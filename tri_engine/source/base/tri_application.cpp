
#include "base/tri_application.hpp"
#include "base/tri_director.hpp"
#include "base/tri_scene.hpp"
#include "dbg/tri_debugmenu.hpp"
#include "dbg/tri_workbar.hpp"
#include "dbg/tri_draw_primitive.hpp"
#include "dbg/tri_debugpad.hpp"
#include "util/tri_framerate.hpp"
#include "util/tri_counter.hpp"
#include "kernel/tri_kernel.hpp"
#include "gfx/tri_render_system.hpp"
#include "audio/tri_audio_system.hpp"
#include "util/tri_stopwatch.hpp"


namespace {

#define LIMIT_AVG_SUM   3600
t3::Vector<float> render_avg;

bool show_fps_ = false;
bool show_heap_ = false;
bool show_work_bar_ = false;
bool show_work_time_ = false;
bool show_task_ = false;
t3::Workbar cpu_bar_;

t3::Stopwatch system_cost_timer_;
t3::Stopwatch app_cost_timer_;
t3::Stopwatch rendering_cost_timer_;
t3::Stopwatch other_cost_timer_;

double last_system_cost_;
double last_app_cost_;
double last_rendering_cost_;
double last_other_cost_;
float fps_;

bool step_update_ = false;

struct Step {
    void operator ()(int){
        step_update_ = true;
    }
};



bool isSuspending() {
    t3::Director& gs = t3::Director::instance();
    t3::DebugMenu& dm = t3::DebugMenu::instance();
    
    if (gs.isSuspend() || dm.isOpened()) {
        return true;
    }
   
    return false;
}


}   // unname namespace


class ApplicationDebugMenu {
public:
    ApplicationDebugMenu(t3::Application* app)
        : dmf_system_(nullptr, "SYSTEM")
        , dmb_root_menu_(&dmf_system_, "RETURN ROOT MENU", app, &::t3::Application::gotoRootScene)
        , dmb_step_(&dmf_system_, "STEP", 0)

        , dm_show_work_time_(&dmf_system_, "SHOW WORKTIME", show_work_time_, 1)
        , dm_show_work_bar_(&dmf_system_, "SHOW WORKBAR", show_work_bar_, 1)
        , dm_show_heap_(&dmf_system_, "SHOW HEAP", show_heap_, 1)
        , dm_show_task_(&dmf_system_, "SHOW TASK", show_task_, 1)
    {
        t3::Director::instance().registryToDebugMenu(dmf_system_);
        render_avg.reserve(LIMIT_AVG_SUM);
    }
    
    
    t3::DebugMenuFrame& getSystemDebugMenuRoot() {
        return dmf_system_;
    };
    
    
private:
    t3::DebugMenuFrame dmf_system_;
    t3::DebugMenuButtonMethod<t3::Application> dmb_root_menu_;
    t3::DebugMenuButtonFunctor<Step> dmb_step_;

    t3::DebugMenuItem<bool> dm_show_work_time_;
    t3::DebugMenuItem<bool> dm_show_work_bar_;
    t3::DebugMenuItem<bool> dm_show_heap_;
    t3::DebugMenuItem<bool> dm_show_task_;
};


namespace t3 {


void initializeTriEngine(
    int width,
    int height,
    const char* const title
) {
    
    //  プラットフォームの初期化
    platform::initializePlatform();
    platform::createWindow(width, height, title);
    
    //  ファイルシステムベースパス設定
    FilePath::setBaseDirectory(platform::getDeviceFilePath());

    //  マネージャインスタンス生成
    Director::createInstance();
    DebugMenu::createInstance();
    SceneManager::createInstance();
    
    //  初期化
    Director::instance().initializeGameSystem();
    
    t3::Director& d = t3::Director::instance();
    d.realScreenSize(
        Vec2(
            width,
            height
        )
    );
    T3_TRACE("Initialize TriEngine.\n");
    T3_TRACE("screen width %d  height %d\n", width, height);
}



inline namespace base {


Application::Application()
    : root_scene_generator_(nullptr)
    , system_menu_(nullptr)
    , last_scene_change_frame_(0)
    , fps_timer_()
{
}

Application::~Application()
{
}

bool Application::isActive() const {
    return !Director::instance().isExitRequest();
}


void Application::initializeWorkBar() {
    
    Director& d = Director::instance();
    const Point2& screen_size = d.virtualScreenSize();
    Point2 half_screen_size = screen_size / 2;
    
    //  ワークバーの配置
    int cpu_bar_margin = 70;
    cpu_bar_.position(Vec2(-half_screen_size.x_ + (cpu_bar_margin / 2), -half_screen_size.y_ + 10));
    cpu_bar_.setLimitWidthPixel(screen_size.x_ - cpu_bar_margin);
    
    //  ワークバーの色
    cpu_bar_.setColor(0, Color::blue());
    cpu_bar_.setColor(1, Color::red());
    cpu_bar_.setColor(2, Color::green());
    cpu_bar_.setColor(3, Color::magenta());
    
}


void Application::initializeApplication()
{
    T3_NULL_ASSERT(root_scene_generator_);
    SceneManager::instance().forceChangeScene(root_scene_generator_);

    //  レンダリングシステムの初期化
    t3::RenderSystem::initializeRenderSystem();

    //  オーディオシステムの初期化
    t3::AudioSystem::initializeAudioSystem();

    //  システムデバッグメニュー登録
    system_menu_.reset(T3_SYS_NEW ApplicationDebugMenu(this));
    
    DebugMenu& debug_menu_root = DebugMenu::instance();
    system_menu_->getSystemDebugMenuRoot().attachSelf(
        debug_menu_root.getMenuRoot()
    );
    
    //  ワークバー初期化
    initializeWorkBar();

    
    //  デバッグ文字描画の初期化
    initializeDebugPrint();
    initializeDrawPrimitive();
   

    //  ゲームの初期化
    initializeGame();

}


void Application::updateApplication()
{
    system_cost_timer_.start();     // system cost 計測開始

    platform::beginUpdate();


    fps_timer_.end();
    fps_timer_.start();

    //  delta time取得
    float delta_time = fps_timer_.interval();
    //  ブレークポイント貼ってる時に異常な数値になる為、最大でも１０フレの遅延に収める
    clampMaximum(delta_time, frameSec<10>());


    //  FPS表示
    if (show_fps_) {
        if ((frame_counter_.now() % 10) == 0) {
            fps_ =  60.0f / (delta_time / frameToSec(1));
        }
        t3::printDisplay(0, 10, "FPS %.1f",fps_);

        float sum_render = 0;
        for (float a : render_avg) {
            sum_render += a;
        }
    
        //  ドローコール数
        t3::printDisplay(140, 10, "DC:%d",
            t3::RenderSystem::getDrawCallCount()
        );
        t3::RenderSystem::resetDrawCallCount();
    }
    
    
    
    SceneManager& sm = SceneManager::instance();
    Director& gs = Director::instance();
    DebugMenu& dm = DebugMenu::instance();

    //  ゲームスピード変更
    float game_speed = gs.getGameSpeed();
    delta_time *= game_speed;
    
    dm.update(delta_time);
    
    if (!isSuspend()) {
        gs.update(delta_time);
    }
    //  レイヤーの更新
    RenderLayer::updateLayers(gs.layers(), delta_time);

    
    system_cost_timer_.end();       // system cost 計測終了
    app_cost_timer_.start();       // app cost 計測開始

    //  シーンの更新
    if (isSuspend()) {
        //  サスペンド中
        gs.suspend(delta_time);
        sm.suspendScene(delta_time);
    } else {
        //  更新中
        sm.updateScene(delta_time);
        
        //  デバッグメニュー開く
        if (isDebugMenuOpenRequest()) {
            dm.openMenu();
        }
    }
    
    platform::endUpdate();


}

void Application::renderApplication()
{
    Director& gs = Director::instance();
    DebugMenu& dm = DebugMenu::instance();

    app_cost_timer_.end();              // app cost 計測終了
    
    //  シーン描画
    beginRender();


    //  デバッグメニュー描画
    dm.render();
    
    

    //  CPU負荷可視化
    if (show_work_bar_){
        cpu_bar_.setParam(0, system_cost_timer_.interval());
        cpu_bar_.setParam(1, app_cost_timer_.interval());
        cpu_bar_.setParam(2, rendering_cost_timer_.interval());
        cpu_bar_.setParam(3, other_cost_timer_.interval());
    }
    
    if (render_avg.size() < LIMIT_AVG_SUM) {
        render_avg.push_back(rendering_cost_timer_.interval());
    }

    rendering_cost_timer_.start();      // rendering cost 計算開始
    //  レイヤーの描画
    RenderLayer::drawLayers(gs.layers());
    rendering_cost_timer_.end();           // rendering cost 計算終了

    if (show_work_bar_) {
        cpu_bar_.draw();
    }

    SceneManager& sm = SceneManager::instance();
    sm.debugRender();

    //  描画終了
    endRender();
    other_cost_timer_.start();


    //  コスト表示は数フレームに1回書き換える
    //  毎フレだと速すぎて読めないからね
    if ((frame_counter_.now() % 10) == 0) {
        last_system_cost_ = system_cost_timer_.interval();
        last_app_cost_ = app_cost_timer_.interval();
        last_rendering_cost_ = rendering_cost_timer_.interval();
        last_other_cost_ = other_cost_timer_.interval();
    }
    
    if (show_work_time_) {
        int cost_pos_x = 5;
        int cost_pos_y = 880;
        t3::printDisplay(
            cost_pos_x,
            cost_pos_y,
            Color::white(),
            "sys %2.2fms(%3.2f%%)",
            last_system_cost_ * 1000,
            last_system_cost_ / frameSec<60>() * 100
        );
        t3::printDisplay(
            cost_pos_x,
            cost_pos_y + 16,
            Color::white(),
            "app %2.2fms(%3.2f%%)",
            last_app_cost_ * 1000,
            last_app_cost_ / frameSec<60>() * 100
        );
        t3::printDisplay(
            cost_pos_x,
            cost_pos_y + 32,
            Color::white(),
            "ren %2.2fms(%3.2f%%)",
            last_rendering_cost_ * 1000,
            last_rendering_cost_ / frameSec<60>() * 100
        );
        t3::printDisplay(
            cost_pos_x,
            cost_pos_y + 48,
            Color::white(),
            "oth %2.2fms(%3.2f%%)",
            last_other_cost_ * 1000,
            last_other_cost_ / frameSec<60>() * 100
        );
        
    }
    
    //  タスク表示
    if (show_task_) {
        gs.showTask();
    }
    
    //  ヒープ表示
    if (show_heap_) {
        auto& heaps = t3::HeapManager::heaps();
        int heap_pos_x = 0;
        int heap_pos_y = 28;
        for (auto& heap : heaps) {
            if (!heap.isActive()) {
                continue;
            }
        
            t3::printDisplay(
                heap_pos_x,
                heap_pos_y,
                Color::white(),
                "%s:T(%7u) P(%7u) Node(%4u)",
                heap.name(),
                heap.allocated().byte(),
                heap.peak().byte(),
                heap.nodeCount()
            );
            heap_pos_y += 20;
        }
    }



    //  最後にシーンチェンジ処理
    sm.directScene();
    
    //  シーン切り替わり判定
    if (sm.isSceneChenged()) {
        //  シーンが切り替わったのでデバッグメニューを閉じる
        dm.closeMenu();
        
        uint32_t now_frame = frame_counter_.now();
        HeapManager::dumpAllocateInfo(1, now_frame);
        
        //  シーンが切り替わったタイミングを保存
        last_scene_change_frame_ = now_frame;
    }

    other_cost_timer_.end();

}


void Application::terminateApplication() {
    //  ゲームの終了処理
    terminateGame();
    
    //  プラットフォームの後片付け
    platform::terminatePlatform();
}


bool Application::isDebugMenuOpenRequest() {

    bool result = false;

#if DEBUG

    //  パッド操作でのオープンリクエスト
    const Pad& pad = debugPad();
    
    if (pad.isPress(Pad::BUTTON_A)) {
        result = true;
    }
    
    
    //  ポインティングでのオープンリクエスト
    const Pointing& pointing = Director::input().pointing();
    if (pointing.isDoubleClick() /*&& pointing.getPointingCount() == 3*/) {
        result = true;
    }
#endif // DEBUG
    return result;
}

bool Application::isSuspend() const {
    //  ステップ実行フック
    if (step_update_) {
        step_update_ = false;
        return false;
    }
    
    //  強制シーンチェンジ時もサスペンドを解く
    SceneManager& sm = SceneManager::instance();
    if (sm.isForceChangeRequested()) {
        return false;
    }

    //  サスペンド中か判定
   if (isSuspending()) {
       return true;
   }


    return false;
}



void Application::beginRender() {
    
    RenderSystem::clearColor(Color::black());
    RenderSystem::clearBuffer(true, true, false);
}


void Application::endRender() {
    RenderSystem::swapBuffers();
}

void Application::gotoRootScene() {
    t3::SceneManager::instance().forceChangeScene(root_scene_generator_);
}





}   // namespace base
}   // namespace t3


