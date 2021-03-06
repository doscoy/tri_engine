////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


//  include
#include "core/base/tri_application.hpp"
#include "core/base/tri_director.hpp"
#include "core/base/tri_scene.hpp"
#include "core/debug/tri_debugmenu.hpp"
#include "core/debug/tri_workbar.hpp"
#include "core/debug/tri_draw_primitive.hpp"
#include "core/debug/tri_print.hpp"
#include "core/debug/tri_debugpad.hpp"
#include "core/utility/tri_framerate.hpp"
#include "core/utility/tri_counter.hpp"
#include "core/kernel/tri_kernel.hpp"
#include "core/utility/tri_stopwatch.hpp"
#include "core/kernel/memory/tri_memory_pool.hpp"
#include "core/kernel/memory/tri_heap.hpp"
#include "core/base/tri_screen_manager.hpp"

TRI_CORE_NS_BEGIN


namespace {

//  処理コスト計算
#define LIMIT_AVG_SUM   3600    //  10秒分の平均を取る
t3::Vector<float> render_avg;   //  10秒分の値格納用


#if DEBUG
//  デバッグモード時に各種表示を行うか判定するフラグ
bool show_fps_ = true;          // FPS
bool show_heap_ = false;        // ヒープ容量（数値）
bool show_heap_bar_ = false;    // ヒープ容量（バー）
bool show_mem_pool_ = false;    // メモリプール容量
bool show_work_bar_ = false;    // CPUコスト（バー）
bool show_work_time_ = false;   // CPUコスト（数値）
bool show_task_ = false;        // タスク一覧

#endif // DEBUG


t3::Workbar cpu_bar_;   // CPUバー表示用

t3::Stopwatch system_cost_timer_;       // システムコストタイマー
t3::Stopwatch app_cost_timer_;          // アプリコストタイマー
t3::Stopwatch rendering_cost_timer_;    // 描画コストタイマー
t3::Stopwatch other_cost_timer_;        // その他のコストタイマー
t3::Stopwatch debug_cost_timer_;        // デバッグ機能コストタイマー

double last_system_cost_;       //  最後のシステムコスト
double last_app_cost_;          // 最後のアプリコスト
double last_rendering_cost_;    // 最後の描画コスト
double last_other_cost_;        // 最後のその他のコスト

bool step_update_ = false;      // ステップ実行用フラグ

//  ステップ実行ファンクタ
struct Step {
    void operator ()(int){
        step_update_ = true;
    }
};


}   // unname namespace




#if DEBUG
///
/// デバッグメニュー
class ApplicationDebugMenu {
public:
    ///
    /// コンストラクタ
    ApplicationDebugMenu(t3::Application* app)  //  いつでもルートメニューに戻れるようアプリケーションのインスタンスを受ける
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
    
    
    ///
    /// デバッグメニューのルートを取得
    t3::DebugMenuFrame& getSystemDebugMenuRoot() {
        return dmf_system_;
    };
    
    
private:
    //  システムメニュー
    t3::DebugMenuFrame dmf_system_;
    
    //  ルートシーンに戻るデバメボタン
    t3::DebugMenuButtonMethod<t3::Application> dmb_root_menu_;
    
    //  ステップ実行用デバメボタン
    t3::DebugMenuButtonFunctor<Step> dmb_step_;
    
    //  処理時間の表示・非表示切り替え
    t3::DebugMenuItem<bool> dm_show_work_time_;
    
    //  処理バーの表示・非表示切り替え
    t3::DebugMenuItem<bool> dm_show_work_bar_;
    
    //  ヒープの表示・非表示切り替え
    t3::DebugMenuItem<bool> dm_show_heap_;
    
    //  タスクの表示・非表示切り替え
    t3::DebugMenuItem<bool> dm_show_task_;
};
#endif // DEBUG


///
/// トライエンジンのシステム初期化
bool initializeTriEngine(
    int width,              ///< 画面横幅
    int height,             ///< 画面縦幅
    const char* const title ///< アプリタイトル
) {
    
    //  プラットフォームの初期化
    if (!cross::initializePlatform(width, height, title)) {
        return false;
    }

    //  マネージャインスタンス生成
    Director::createInstance();
    
    //  初期化
    auto& d = t3::Director::instance();
    d.initializeDirector();
    
    //  デバイスの画面サイズ設定
    auto& screen_mgr = t3::ScreenManager::instance();
    screen_mgr.deviceScreenSize(
        Vec2(
            static_cast<float>(width),
            static_cast<float>(height)
        )
    );
    
    //  準備完了
    T3_SYSTEM_LOG("Initialize TriEngine.\n");
    T3_SYSTEM_LOG("screen width %d  height %d\n", width, height);
    
    
#if DEBUG
    show_fps_ = true;
    show_mem_pool_ = true;
    show_work_bar_ = true;
#endif


    return true;
}

///
/// トライエンジンのシステム後片付け
void terminateTriEngine() {
    //  マネージャ破棄
    auto& d = Director::instance();
    d.terminateDirector();
    Director::destroyInstance();
    cross::terminatePlatform();
}



///
/// コンストラクタ
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

///
/// デストラクタ
Application::~Application()
{
}

///
/// アプリケーションがアクティブか判定
bool Application::isActive() const {
    return !Director::instance().isExitRequest();
}

///
/// ワークバーの初期化
void Application::initializeWorkBar() {
    
    auto& screen_mgr = ScreenManager::instance();
    const Vec2& screen_size = screen_mgr.virtualScreenSize();
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


///
/// アプリケーション初期化
void Application::initializeApplication()
{
    T3_NULL_ASSERT(root_scene_generator_);
    //  ルートシーン作成
    auto& d = Director::instance();
    d.rootTask()->addTaskRequest(root_scene_generator_);


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
   
    auto& screen_mgr = ScreenManager::instance();
    cross::RenderSystem::setViewport(
        0,
        0,
        screen_mgr.deviceScreenSize().x_,
        screen_mgr.deviceScreenSize().y_
    );
    
    d.setupFinalLayer();

    //  ゲームの初期化
    initializeGame();
}


///
/// アプリケーション更新
void Application::updateApplication() {
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
    
    
    
    auto& director = Director::instance();
    DebugMenu& dm = DebugMenu::instance();

    //  ゲームスピード変更
    float game_speed = director.getGameSpeed();
    delta_time *= game_speed;
    
    
    director.update(delta_time);


    
    system_cost_timer_.end();       // system cost 計測終了
    app_cost_timer_.start();       // app cost 計測開始


    //  デバッグメニュー開く
    if (isDebugMenuOpenRequest()) {
        dm.openMenu();
    }
    
    cross::endUpdate();
}

///
/// アプリケーションの描画
void Application::renderApplication() {
    T3_RENDER_ASSERT();

    auto& director = Director::instance();
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

    debug_cost_timer_.end();
    rendering_cost_timer_.start();      // rendering cost 計算開始
    //  レイヤーの描画
    LayerBase::drawLayers(director.layers());
    rendering_cost_timer_.end();           // rendering cost 計算終了

    //  描画終了
    endRender();
    other_cost_timer_.start();
    T3_RENDER_ASSERT();

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
    T3_RENDER_ASSERT();
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
            "sys %2.2fms(%3.2f%%)",
            last_system_cost_ * 1000,
            last_system_cost_ / frameSec<60>() * 100
        );
        T3_PRINT_DISP(
            cost_pos_x,
            cost_pos_y + 16,
            "app %2.2fms(%3.2f%%)",
            last_app_cost_ * 1000,
            last_app_cost_ / frameSec<60>() * 100
        );
        T3_PRINT_DISP(
            cost_pos_x,
            cost_pos_y + 32,
            "ren %2.2fms(%3.2f%%)",
            last_rendering_cost_ * 1000,
            last_rendering_cost_ / frameSec<60>() * 100
        );
        T3_PRINT_DISP(
            cost_pos_x,
            cost_pos_y + 48,
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


///
/// 後片付け
void Application::terminateApplication() {
    //  ゲームの終了処理
    terminateGame();    
}

///
/// デバッグメニューの表示リクエスト
bool Application::isDebugMenuOpenRequest() {

    bool result = false;

#if DEBUG

    //  パッド操作でのオープンリクエスト
    const Pad& pad = debugPad();
    
    if (pad.isPress(Pad::BUTTON_A)) {
        result = true;
    }
    
    
    //  ポインティングでのオープンリクエスト
    auto& director = Director::instance();
    const Pointing& pointing = director.input().pointing();
    if (pointing.isDoubleClick() /*&& pointing.getPointingCount() == 3*/) {
        result = true;
    }
#endif // DEBUG
    return result;
}

///
/// アプリケーションのサスペンド判定
bool Application::isSuspend() const {

    auto& dm = t3::DebugMenu::instance();
    
    if (dm.isOpened()) {
        return true;
    }
   
    return false;
}


///
/// 描画開始
void Application::beginRender() {
    auto& director = Director::instance();

    //  クリアカラー設定
    auto& c = director.getClearColor();
    cross::RenderSystem::clearColor(c.redFloat(), c.greenFloat(), c.blueFloat(), c.alphaFloat());
    cross::RenderSystem::clearBuffer(true, true, false);

}

///
/// 描画終了
void Application::endRender() {
    cross::endRender();
}

///
/// ルートシーンへ飛ぶ
void Application::gotoRootScene() {
    t3::SceneManager::instance().forceChangeScene(root_scene_generator_);
}


//-----------

///
/// アプリケーションのC言語風呼び出しインターフェース
Application* app_ = nullptr;
void setApplication(Application& app) {
    app_ = &app;
}

void initializeApplication() {
    app_->initializeApplication();
}


void terminateApplication() {
    T3_RENDER_ASSERT();
    app_->terminateApplication();
}


void updateApplication() {
    app_->updateApplication();
}


void renderApplication() {
    app_->renderApplication();
}


bool isActiveApplication() {
    return app_->isActive();
}


TRI_CORE_NS_END


