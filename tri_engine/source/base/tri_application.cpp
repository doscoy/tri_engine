
#include "base/tri_application.hpp"
#include "base/tri_director.hpp"
#include "base/tri_scene.hpp"
#include "dbg/tri_debugmenu.hpp"
#include "dbg/tri_workbar.hpp"
#include "dbg/tri_draw_primitive.hpp"
#include "dbg/tri_print.hpp"
#include "dbg/tri_debugpad.hpp"
#include "util/tri_framerate.hpp"
#include "util/tri_counter.hpp"
#include "kernel/tri_kernel.hpp"


#include "util/tri_stopwatch.hpp"
#include "kernel/memory/tri_memory_pool.hpp"
#include "kernel/memory/tri_heap.hpp"



namespace {

#define LIMIT_AVG_SUM   3600
t3::Vector<float> render_avg;

#if DEBUG
bool show_fps_ = true;
bool show_heap_ = false;
bool show_heap_bar_ = false;
bool show_mem_pool_ = false;
bool show_work_bar_ = false;
bool show_work_time_ = false;
bool show_task_ = false;

#endif // DEBUG
t3::Workbar cpu_bar_;

t3::Stopwatch system_cost_timer_;
t3::Stopwatch app_cost_timer_;
t3::Stopwatch rendering_cost_timer_;
t3::Stopwatch other_cost_timer_;
t3::Stopwatch debug_cost_timer_;

double last_system_cost_;
double last_app_cost_;
double last_rendering_cost_;
double last_other_cost_;

bool step_update_ = false;

struct Step {
    void operator ()(int){
        step_update_ = true;
    }
};





}   // unname namespace

#if DEBUG
class ApplicationDebugMenu {
public:
    ApplicationDebugMenu(t3::Application* app)
        : dmf_system_(nullptr, "SYSTEM")
        , dmb_root_menu_(&dmf_system_, "RETURN ROOT MENU", app, &::t3::Application::gotoRootScene)
        , dmb_step_(&dmf_system_, "STEP", 0)

        , dm_show_work_time_(&dmf_system_, "SHOW WORKTIME", show_work_time_)
        , dm_show_work_bar_(&dmf_system_, "SHOW WORKBAR", show_work_bar_)
        , dm_show_heap_(&dmf_system_, "SHOW HEAP", show_heap_)
        , dm_show_task_(&dmf_system_, "SHOW TASK", show_task_)
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
#endif // DEBUG

namespace t3 {


bool initializeTriEngine(
    int width,
    int height,
    const char* const title
) {
    
    //  プラットフォームの初期化
    if (!cross::initializePlatform(width, height, title)) {
        return false;
    }
    

    //  マネージャインスタンス生成
    Director::createInstance();
    
    //  初期化
    Director::instance().initializeDirector();
    
    auto& d = t3::Director::instance();
    d.deviceScreenSize(
        Vec2(
            static_cast<float>(width),
            static_cast<float>(height)
        )
    );
    
    T3_TRACE("Initialize TriEngine.\n");
    T3_TRACE("screen width %d  height %d\n", width, height);
    
    
#if DEBUG
    show_fps_ = true;
    show_mem_pool_ = true;
    show_work_bar_ = true;
#endif


    return true;
}

void terminateTriEngine() {
    T3_ASSERT(!cross::RenderSystem::isError());
    auto& d = Director::instance();
    d.terminateDirector();
    Director::destroyInstance();
    cross::terminatePlatform();
}



Application::Application()
    : root_scene_generator_(nullptr)
#if DEBUG
    , system_menu_(nullptr)
#endif // DEBUG
    , last_scene_change_frame_(0)
    , fps_timer_()
    , fps_stack_()
    , fps_(60.0f)
{
}

Application::~Application()
{
}

bool Application::isActive() const {
    return !Director::instance().isExitRequest();
}


void Application::initializeWorkBar() {
    
    auto& d = Director::instance();
    const Vec2& screen_size = d.virtualScreenSize();
    Vec2 half_screen_size = screen_size / 2;
    
    //  ワークバーの配置
    int cpu_bar_margin = 70;
    cpu_bar_.position(
        Vec2(-half_screen_size.x_ + (cpu_bar_margin / 2), -half_screen_size.y_ + 10)
    );
    cpu_bar_.setLimitWidthPixel(
		static_cast<int>(screen_size.x_) - cpu_bar_margin
	);
    
    //  ワークバーの色
    cpu_bar_.setColor(0, color_sample::blue());
    cpu_bar_.setColor(1, color_sample::red());
    cpu_bar_.setColor(2, color_sample::green());
    cpu_bar_.setColor(3, color_sample::magenta());
    
}


void Application::initializeApplication()
{
    T3_NULL_ASSERT(root_scene_generator_);
    SceneManager::instance().forceChangeScene(root_scene_generator_);


#if DEBUG
    //  システムデバッグメニュー登録
    system_menu_.reset(T3_SYS_NEW ApplicationDebugMenu(this));
    
    DebugMenu& debug_menu_root = DebugMenu::instance();
    system_menu_->getSystemDebugMenuRoot().attachSelf(
        debug_menu_root.rootMenu()
    );
#endif // DEBUG
    
    //  ワークバー初期化
    initializeWorkBar();

    
    //  デバッグ文字描画の初期化

    initializeDrawPrimitive();
   

    //  ゲームの初期化
    initializeGame();
    T3_ASSERT(!cross::RenderSystem::isError());

}


void Application::updateApplication()
{
    T3_ASSERT(!cross::RenderSystem::isError());
    system_cost_timer_.start();     // system cost 計測開始

    cross::beginUpdate();


    fps_timer_.end();
    fps_timer_.start();

    //  delta time取得
    float delta_time = fps_timer_.interval();
    //  ブレークポイント貼ってる時に異常な数値になる為、最大でも１０フレの遅延に収める
    clampMaximum(delta_time, frameSec<30>());


    //  FPS表示
#if DEBUG
    if (show_fps_) {
        //  直近数フレームの平均値を表示
        
        //  fpsを保存
        float current_fps = 60.0f / (delta_time / frameToSec(1));
    
        const size_t fps_size = fps_stack_.size();
        for (int fps_idx = 1; fps_idx < fps_size; ++fps_idx) {
            fps_stack_[fps_idx-1] = fps_stack_[fps_idx];
        }
        fps_stack_[fps_size-1] = current_fps;
    
        //  描画は１０フレに１回
        if (frame_counter_.now() % 10 == 0) {
            //  平均計算
            float fps_avg = 0.0f;
        
            for (auto& v : fps_stack_) {
                fps_avg += v;
            }
            fps_avg /= fps_size;
            fps_ = fps_avg;
        }
        T3_PRINT_DISP(0, 0, "FPS %.1f",fps_);

        float sum_render = 0;
        for (float a : render_avg) {
            sum_render += a;
        }
    
        //  ドローコール数
        T3_PRINT_DISP(140, 0, "DC:%d",
            cross::RenderSystem::getDrawCallCount()
        );
        cross::RenderSystem::resetDrawCallCount();
    }
#endif // DEBUG
    
    
    
    auto& gs = Director::instance();
    DebugMenu& dm = DebugMenu::instance();

    //  ゲームスピード変更
    float game_speed = gs.getGameSpeed();
    delta_time *= game_speed;
    
    
    gs.update(delta_time);


    
    system_cost_timer_.end();       // system cost 計測終了
    app_cost_timer_.start();       // app cost 計測開始


    //  デバッグメニュー開く
    if (isDebugMenuOpenRequest()) {
        dm.openMenu();
    }
    
    cross::endUpdate();
    T3_ASSERT(!cross::RenderSystem::isError());


}

void Application::renderApplication() {
    T3_ASSERT(!cross::RenderSystem::isError());

    auto& gs = Director::instance();
    DebugMenu& dm = DebugMenu::instance();

    app_cost_timer_.end();              // app cost 計測終了
    
    //  シーン描画
    beginRender();
    debug_cost_timer_.start();

    //  デバッグメニュー描画
    dm.render();
    
    

    
    if (render_avg.size() < LIMIT_AVG_SUM) {
        render_avg.push_back(rendering_cost_timer_.interval());
    }
    


    auto& sm = SceneManager::instance();
    sm.debugRender();

    debug_cost_timer_.end();
    rendering_cost_timer_.start();      // rendering cost 計算開始
    //  レイヤーの描画
    RenderLayer::drawLayers(gs.layers());
    rendering_cost_timer_.end();           // rendering cost 計算終了

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
    
#if DEBUG
    debugPrinting();
#endif // DEBUG


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

void Application::debugPrinting() {

#if DEBUG
    auto& gs = Director::instance();




   //  CPU負荷可視化
    if (show_work_bar_){
        cpu_bar_.setParam(0, system_cost_timer_.interval());
        cpu_bar_.setParam(1, app_cost_timer_.interval());
        cpu_bar_.setParam(2, rendering_cost_timer_.interval());
        cpu_bar_.setParam(3, other_cost_timer_.interval());
        cpu_bar_.setParam(4, debug_cost_timer_.interval());
        
    }
 
    //  ワークバー描画
    if (show_work_bar_) {
     //   cpu_bar_.draw();
    }
    
    
    
    //  メモリバー描画
//  renderMemoryPoolにmutex付けないと落ちる可能性があります
    if (show_heap_bar_) {
        MemoryPool* pool = heapMemoryPool();
        renderMemoryPool(*pool);
    }



    if (show_work_time_) {
        int cost_pos_x = 5;
        int cost_pos_y = 880;
        T3_PRINT_DISP(
            cost_pos_x,
            cost_pos_y,
            color_sample::white(),
            "sys %2.2fms(%3.2f%%)",
            last_system_cost_ * 1000,
            last_system_cost_ / frameSec<60>() * 100
        );
        T3_PRINT_DISP(
            cost_pos_x,
            cost_pos_y + 16,
            color_sample::white(),
            "app %2.2fms(%3.2f%%)",
            last_app_cost_ * 1000,
            last_app_cost_ / frameSec<60>() * 100
        );
        T3_PRINT_DISP(
            cost_pos_x,
            cost_pos_y + 32,
            color_sample::white(),
            "ren %2.2fms(%3.2f%%)",
            last_rendering_cost_ * 1000,
            last_rendering_cost_ / frameSec<60>() * 100
        );
        T3_PRINT_DISP(
            cost_pos_x,
            cost_pos_y + 48,
            color_sample::white(),
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
        int heap_pos_y = 45;
        for (auto& heap : heaps) {
            if (!heap.isActive()) {
                continue;
            }
        
            T3_PRINT_DISP(
                heap_pos_x,
                heap_pos_y,
                color_sample::white(),
                "%s:T(%7u) P(%7u) Node(%4u)",
                heap.name(),
                heap.allocated().byte(),
                heap.peak().byte(),
                heap.nodeCount()
            );
            heap_pos_y += 20;
        }
    }

    //  メモリプール量描画
    if (show_mem_pool_) {
        MemoryPool* heap = heapMemoryPool();
        size_t free_pool = heap->totalFreeSize();
        size_t use_pool = heap->totalUseSize();
        size_t peak_use_size = heap->peakUseSize();
        T3_PRINT_DISP(0, 28, "POOL F(%7u)  U(%7u) P(%7u)", free_pool, use_pool, peak_use_size);

    }
#endif

}

void Application::terminateApplication() {
    //  ゲームの終了処理
    terminateGame();    
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

    auto& director = t3::Director::instance();
    auto& dm = t3::DebugMenu::instance();
    
    if (director.isSuspend() || dm.isOpened()) {
        return true;
    }
   
    return false;
}



void Application::beginRender() {
    auto& c = t3::Director::getClearColor();
    cross::RenderSystem::clearColor(c.redFloat(), c.greenFloat(), c.blueFloat(), c.alphaFloat());
    cross::RenderSystem::clearBuffer(true, true, false);

}


void Application::endRender() {
    cross::endRender();
}

void Application::gotoRootScene() {
    t3::SceneManager::instance().forceChangeScene(root_scene_generator_);
}


//-----------
Application* app_ = nullptr;
void setApplication(Application& app) {
    app_ = &app;
}

void initializeApplication() {
    app_->initializeApplication();
}


void terminateApplication() {
    T3_ASSERT(!cross::RenderSystem::isError());
    app_->terminateApplication();
}


void updateApplication() {
    app_->updateApplication();
}


void renderApplication() {
    app_->renderApplication();
}


bool isActiveApplication() {
    T3_ASSERT(!cross::RenderSystem::isError());
    return app_->isActive();
}


}   // namespace t3


