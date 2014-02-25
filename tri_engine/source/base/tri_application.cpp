
#include "base/tri_application.hpp"
#include "base/tri_game_system.hpp"
#include "base/tri_scene.hpp"
#include "dbg/tri_debugmenu.hpp"
#include "dbg/tri_stopwatch.hpp"
#include "dbg/tri_workbar.hpp"
#include "dbg/tri_draw_primitive.hpp"
#include "dbg/tri_debugpad.hpp"
#include "util/tri_framerate.hpp"
#include "util/tri_counter.hpp"
#include "kernel/tri_kernel.hpp"
#include "gfx/tri_render_system.hpp"



namespace {


bool show_work_bar_ = true;
bool show_work_time_ = true;
t3::Workbar cpu_bar_;

t3::Stopwatch system_cost_timer_;
t3::Stopwatch app_cost_timer_;
t3::Stopwatch rendering_cost_timer_;
t3::Stopwatch other_cost_timer_;

double last_system_cost_;
double last_app_cost_;
double last_rendering_cost_;
double last_other_cost_;

bool step_update_ = false;

struct Step
{
    void operator ()( int ){
        step_update_ = true;
    }
};

struct DumpAllocatorLog
{
    void operator ()( int ){
        t3::default_allocator_.getAllocationRecorder().dump();
    }
};



bool isSuspending()
{
    t3::GameSystem& gs = t3::GameSystem::getInstance();
    t3::DebugMenu& dm = t3::DebugMenu::getInstance();
    
    if( gs.isSuspend() || dm.isOpened() ){
        return true;
    }
   
    return false;
}


}   // unname namespace


class ApplicationDebugMenu
{
public:
    ApplicationDebugMenu(t3::Application* app)
        : dmf_system_( nullptr, "SYSTEM" )
        , dmb_root_menu_( &dmf_system_, "RETURN ROOT MENU", app, &::t3::Application::gotoRootScene )
        , dmb_step_( &dmf_system_, "STEP", 0 )
        , dmb_dump_allocater_log_( &dmf_system_, "DUMP ALLOCATE LOG", 0 )
        , dmi_show_work_time_( &dmf_system_, "SHOW WORKTIME", show_work_time_, 1 )
        , dmi_show_work_bar_( &dmf_system_, "SHOW WORKBAR", show_work_bar_, 1 )
    {
        t3::GameSystem::getInstance().registryToDebugMenu( dmf_system_ );
    }
    
    
    t3::DebugMenuFrame& getSystemDebugMenuRoot() {
        return dmf_system_;
    };
    
    
private:
    t3::DebugMenuFrame dmf_system_;
    t3::DebugMenuButtonMethod<t3::Application> dmb_root_menu_;
    t3::DebugMenuButtonFunctor<Step> dmb_step_;
    t3::DebugMenuButtonFunctor<DumpAllocatorLog> dmb_dump_allocater_log_;
    t3::DebugMenuItem<bool> dmi_show_work_time_;
    t3::DebugMenuItem<bool> dmi_show_work_bar_;
};


namespace t3 {


void initializeTriEngine(int width, int height, const char* title) {
    
    //  プラットフォームの初期化
    platform::initializePlatform();
    platform::createWindow(width, height, title);
    
    DebugMenu::createInstance();
    GameSystem::createInstance();
    SceneManager::createInstance();
    
    
    t3::GameSystem* game_system = t3::GameSystem::getInstancePointer();
    game_system->setScreenSize(
        Point2(
            width,
            height
        )
    );
}









inline namespace base {

int Application::run(t3::SceneGenerator* root_scene_generator) {

    t3::Application app(root_scene_generator);
    
    
    //  アプリの初期化
    app.initializeApplication();
    
    //  ゲームシステム
    GameSystem& gs = GameSystem::getInstance();

    float default_delta_time = frameSec<60>();
    //  main loop
    while (!gs.isExitRequest()) {
        platform::beginMainLoop();
        
        //  アプリケーションの更新
        app.update(default_delta_time);
        
        platform::endMainLoop();

    }
    
    
    
    return 0;
}


Application::Application(
    SceneGenerator* root_scene_generator
)   : root_scene_generator_( root_scene_generator )
    , system_menu_( nullptr )
    , last_scene_change_frame_( 0 )
{
}

Application::~Application()
{
}

void Application::initializeApplication()
{
    SceneManager::getInstance().forceChangeScene( root_scene_generator_ );
    GameSystem& game_system = GameSystem::getInstance();
    
    //  ワークバーの配置
    cpu_bar_.setPosition(
        Vec2(
             1,
             game_system.getScreenSize().y_ -5
        )
    );


    //  システムデバッグメニュー登録
    system_menu_.reset( T3_NEW ApplicationDebugMenu(this) );

    DebugMenu& debug_menu_root = DebugMenu::getInstance();
    system_menu_->getSystemDebugMenuRoot().attachSelf(
        debug_menu_root.getMenuRoot()
    );
    
    //  レンダリングシステムの初期化
    t3::RenderSystem::initializeRenderSystem();
    
    //  デバッグ文字描画の初期化
    initializeDebugPrint();
    initializeTrace();

}


void Application::update(tick_t tick)
{

    other_cost_timer_.end();
    system_cost_timer_.start();     // system cost 計測開始
    
    SceneManager& sm = SceneManager::getInstance();
    GameSystem& gs = GameSystem::getInstance();
    DebugMenu& dm = DebugMenu::getInstance();
    
    
    dm.update(tick);
    gs.update(tick);

    //  レイヤーの更新
    gfx::updateLayers(gs.getLaysers(), tick);

    
    system_cost_timer_.end();       // system cost 計測終了
    app_cost_timer_.start();       // app cost 計測開始

    //  シーンの更新
    if (isSuspend()) {
        //  サスペンド中
        gs.suspend(tick);
        sm.suspendScene(tick);
    }
    else {
        //  更新中
        sm.updateScene(tick);
        
        //  デバッグメニュー開く
        if (isDebugMenuOpenRequest()) {
            dm.openMenu();
        }
    }
    
    app_cost_timer_.end();              // app cost 計測終了
    rendering_cost_timer_.start();      // rendering cost 計算開始
    
    //  シーン描画
    beginRender();
    
    //  デバッグメニュー描画
    dm.render();
    
    //  レイヤーの描画
    gfx::drawLayers(gs.getLaysers());
    
    
    //  CPU負荷可視化
    if ( show_work_bar_ ){
        cpu_bar_.setParam(0, system_cost_timer_.interval());
        cpu_bar_.setParam(1, app_cost_timer_.interval());
        cpu_bar_.setParam(2, rendering_cost_timer_.interval());
        cpu_bar_.setParam(3, other_cost_timer_.interval());
        cpu_bar_.draw();
    }
    rendering_cost_timer_.end();           // rendering cost 計算終了

    //  描画終了
    endRender();
    other_cost_timer_.start();
    
    //  コスト表示は数フレームに1回書き換える
    //  毎フレだと速すぎて読めないからね
    if ((frame_counter_.now() % 15) == 0) {
        last_system_cost_ = system_cost_timer_.interval();
        last_app_cost_ = app_cost_timer_.interval();
        last_rendering_cost_ = rendering_cost_timer_.interval();
        last_other_cost_ = other_cost_timer_.interval();
    }
    
    if (show_work_time_) {
        t3::printDisplay(
            940,
            640,
            Color::white(),
            "sys %2.1fms(%3.1f%%)",
            last_system_cost_ * 1000,
            last_system_cost_ / frameSec<60>() * 100
        );
        t3::printDisplay(
            940,
            656,
            Color::white(),
            "app %2.1fms(%3.1f%%)",
            last_app_cost_ * 1000,
            last_app_cost_ / frameSec<60>() * 100
        );
        t3::printDisplay(
            940,
            672,
            Color::white(),
            "ren %2.1fms(%3.1f%%)",
            last_rendering_cost_ * 1000,
            last_rendering_cost_ / frameSec<60>() * 100
        );
        t3::printDisplay(
            940,
            688,
            Color::white(),
            "oth %2.1fms(%3.1f%%)",
            last_other_cost_ * 1000,
            last_other_cost_ / frameSec<60>() * 100
        );
    }

    //  最後にシーンチェンジ処理
    sm.directScene();
    
    //  シーン切り替わり判定
    if (sm.isSceneChenged()) {
        //  シーンが切り替わったのでデバッグメニューを閉じる
        dm.closeMenu();

        //  メモリリークを検出
        default_allocator_.getAllocationRecorder().dump(
            last_scene_change_frame_,
            frame_counter_.now()-1
        );

        //  シーンが切り替わったタイミングを保存
        last_scene_change_frame_ = frame_counter_.now();
    }
}

bool Application::isDebugMenuOpenRequest() {
    const Pad& pad = debugPad();
    
    bool result = false;
    if (pad.isPress(Pad::BUTTON_X)) {
        result = true;
    }
    
    return result;
}

bool Application::isSuspend() const {
    //  ステップ実行フック
    if (step_update_) {
        step_update_ = false;
        return false;
    }
    
    //  強制シーンチェンジ時もサスペンドを解く
    SceneManager& sm = SceneManager::getInstance();
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
    RenderSystem::clearBuffer(true, true, false);
}


void Application::endRender() {
    RenderSystem::swapBuffers();
}

void Application::gotoRootScene() {
    t3::SceneManager::getInstance().forceChangeScene(root_scene_generator_);
}





}   // namespace base
}   // namespace t3


