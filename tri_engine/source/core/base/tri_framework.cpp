////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


//  include
#include "core/base/tri_framework.hpp"
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


#ifdef TRI_DEBUG
//  デバッグモード時に各種表示を行うか判定するフラグ
bool show_fps_ = true;          // FPS
bool show_heap_ = false;        // ヒープ容量（数値）
bool show_heap_bar_ = false;    // ヒープ容量（バー）
bool show_mem_pool_ = false;    // メモリプール容量
bool show_work_bar_ = false;    // CPUコスト（バー）
bool show_work_time_ = false;   // CPUコスト（数値）
bool show_task_ = false;        // タスク一覧

#endif // TRI_DEBUG


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




#ifdef TRI_DEBUG

///
/// デバッグメニュー
class FrameworkDebugMenu {
public:
    ///
    /// コンストラクタ
    FrameworkDebugMenu()
        : dmf_system_(nullptr, "FRAMEWORK")
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
#endif // TRI_DEBUG


//----------------------------------------------------------------------
///
/// コンストラクタ
Framework::Framework()
    : app_(nullptr)
    , next_app_generator_(nullptr)
#ifdef TRI_DEBUG
    , system_menu_(nullptr)
#endif
    , fps_timer_()
    , fps_stack_()
    , fps_(60.0f)
{
}

//----------------------------------------------------------------------
///
/// デストラクタ
Framework::~Framework()
{
}



//----------------------------------------------------------------------
///
/// フレームワーク初期化
bool Framework::initializeFramework(const InitConfiguration& config)
{


    //  プラットフォームの初期化
    if (!cross::initializePlatform(config)) {
        return false;
    }

    //  マネージャインスタンス生成
    auto& director = Director::createInstance();
    
    //  初期化
    director.initializeDirector();
    
    //  デバイスの画面サイズ設定
    auto& screen_mgr = t3::ScreenManager::instance();
    screen_mgr.resizeScreen(
        Vec2(
            static_cast<float>(config.window_width_),
            static_cast<float>(config.window_height_)
        )
    );

    //  仮想スクリーンの画面サイズ設定
    screen_mgr.virtualScreenSize(
        Vec2(
            static_cast<float>(config.virtual_screen_width_),
            static_cast<float>(config.virtual_screen_height_)
        )
    );
    
    

    
    //  準備完了
    T3_SYSTEM_LOG("Initialize TriEngine.\n");
    
    
    //  ワークバー初期化
    initializeWorkBar();

    
    //  デバッグ描画の初期化
    initializeDrawPrimitive();
   
    //  最終描画レイヤー初期化
    director.setupFinalLayer();

    
    
#ifdef TRI_DEBUG
    show_fps_ = true;
    show_mem_pool_ = true;
    show_work_bar_ = true;
#endif





#ifdef TRI_DEBUG
    //  システムデバッグメニュー登録
    system_menu_.reset(T3_SYS_NEW FrameworkDebugMenu);
    
    DebugMenu& debug_menu_root = DebugMenu::instance();
    system_menu_->getSystemDebugMenuRoot().attachSelf(
        debug_menu_root.rootMenu()
    );
#endif // TRI_DEBUG
    

    return true;
}

//----------------------------------------------------------------------

void Framework::terminateFramework() {
    //  マネージャ破棄
    auto& d = Director::instance();
    d.terminateDirector();
    Director::destroyInstance();
    cross::terminatePlatform();

}

//----------------------------------------------------------------------
///
/// アプリケーション更新
void Framework::updateFramework() {
    system_cost_timer_.start();     // system cost 計測開始

    cross::beginUpdate();


    fps_timer_.end();
    fps_timer_.start();

    //  delta time取得
    float dt = fps_timer_.interval();
    //  ブレークポイント貼ってる時に異常な数値になる為、最大でも１０フレの遅延に収める
    clampMaximum(dt, frameSec<30>());


    //  FPS表示
#ifdef TRI_DEBUG
    if (show_fps_) {
        //  直近数フレームの平均値を表示
        
        //  fpsを保存
        float current_fps = 60.0f / (dt / frameToSec(1));
    
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
        T3_PRINT_DISP(8, 0, "DC:%d",
            cross::RenderSystem::getDrawCallCount()
        );
        cross::RenderSystem::resetDrawCallCount();
    }
#endif // TRI_DEBUG
    
    
    
    auto& director = Director::instance();
    DebugMenu& dm = DebugMenu::instance();

    //  ゲームスピード変更
    float game_speed = director.getGameSpeed();
    dt *= game_speed;
    
    FrameInfo frame_info;
    frame_info.deltaTime(dt);
    director.update(frame_info);


    
    system_cost_timer_.end();       // system cost 計測終了
    app_cost_timer_.start();       // app cost 計測開始


    //  デバッグメニュー開く
    if (isDebugMenuOpenRequest()) {
        dm.openMenu();
    }
    
    doUpdateApplication(frame_info);
    
    cross::endUpdate();
}

//----------------------------------------------------------------------
///
/// フレームワークの描画
void Framework::renderFramework() {
    T3_RENDER_ASSERT();

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
    



    debug_cost_timer_.end();
    rendering_cost_timer_.start();      // rendering cost 計算開始
    //  レイヤーの描画
    auto& director = Director::instance();
    director.render();
    doRenderApplication();

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
    
#ifdef TRI_DEBUG
    debugPrinting();
#endif // TRI_DEBUG



    other_cost_timer_.end();
    T3_RENDER_ASSERT();
}


//----------------------------------------------------------------------
///
/// フレームワークがアクティブか判定
bool Framework::isActive() const {
    return !Director::instance().isExitRequest();
}

//----------------------------------------------------------------------
///
/// ワークバーの初期化
void Framework::initializeWorkBar() {
    
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


//----------------------------------------------------------------------

void Framework::debugPrinting() {

#ifdef TRI_DEBUG
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
        T3_PRINT_DISP(
            4,
            1,
            "sys %2.2fms(%3.2f%%)",
            last_system_cost_ * 1000,
            last_system_cost_ / frameSec<60>() * 100
        );
        T3_PRINT_DISP(
            4,
            2,
            "app %2.2fms(%3.2f%%)",
            last_app_cost_ * 1000,
            last_app_cost_ / frameSec<60>() * 100
        );
        T3_PRINT_DISP(
            4,
            3,
            "ren %2.2fms(%3.2f%%)",
            last_rendering_cost_ * 1000,
            last_rendering_cost_ / frameSec<60>() * 100
        );
        T3_PRINT_DISP(
            4,
            4,
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
        int heap_pos_y = 5;
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
            heap_pos_y += 1;
        }
    }

    //  メモリプール量描画
    if (show_mem_pool_) {
        MemoryPool* heap = heapMemoryPool();
        size_t free_pool = heap->totalFreeSize();
        size_t use_pool = heap->totalUseSize();
        size_t peak_use_size = heap->peakUseSize();
        T3_PRINT_DISP(0, 1, "POOL F(%7u)  U(%7u) P(%7u)", free_pool, use_pool, peak_use_size);

    }
#endif

}

//----------------------------------------------------------------------
///
/// デバッグメニューの表示リクエスト
bool Framework::isDebugMenuOpenRequest() {

    bool result = false;

#ifdef TRI_DEBUG

    //  パッド操作でのオープンリクエスト
    const Pad& pad = debugPad();
    
    if (pad.isPress(Pad::BUTTON_HOME)) {
        result = true;
    }
    
    
    //  ポインティングでのオープンリクエスト
    auto& director = Director::instance();
    const Pointing& pointing = director.input().pointing();
    if (pointing.isDoubleClick() /*&& pointing.getPointingCount() == 3*/) {
        result = true;
    }
#endif // TRI_DEBUG
    return result;
}

//----------------------------------------------------------------------
///
/// アプリケーションのサスペンド判定
bool Framework::isSuspend() const {

    auto& dm = t3::DebugMenu::instance();
    
    if (dm.isOpened()) {
        return true;
    }
   
    return false;
}


//----------------------------------------------------------------------
///
/// 描画開始
void Framework::beginRender() {
    auto& director = Director::instance();

    //  クリアカラー設定
    auto c = director.getClearColor();
    cross::RenderSystem::clearColor(c.redFloat(), c.greenFloat(), c.blueFloat(), c.alphaFloat());
    cross::RenderSystem::clearBuffer(true, true, false);

    c = color_sample::black();
    cross::RenderSystem::clearColor(c.redFloat(), c.greenFloat(), c.blueFloat(), c.alphaFloat());

}

//----------------------------------------------------------------------
///
/// 描画終了
void Framework::endRender() {
    cross::endRender();
}


///
/// アプリケーションの更新
void Framework::doUpdateApplication(const FrameInfo& frame_info) {
    //  アプリケーションの切り替え
    if (next_app_generator_) {
        //  アプリケーションの切り替えリクエストがあった
        app_ = next_app_generator_->create();
        next_app_generator_ = nullptr;
    }

    if (app_) {
        if (!app_->isReady()) {
            app_->initializeApplication();
        }
        app_->updateApplication(frame_info);
    }
}


///
///
void Framework::doRenderApplication() {
    if (app_) {
        app_->renderApplication();
    }
}



TRI_CORE_NS_END


