
#include "tri_application.hpp"
#include "tri_game_system.hpp"
#include "tri_scene.hpp"
#include "../dbg/tri_debugmenu.hpp"
#include "../dbg/tri_stopwatch.hpp"
#include "../dbg/tri_workbar.hpp"
#include "../dbg/tri_draw_primitive.hpp"
#include "../dbg/tri_debugpad.hpp"

namespace {

bool workbar_visible_ = true;
t3::Workbar cpu_bar_( 0.0166, 475 );
t3::Stopwatch system_cost_timer_;
t3::Stopwatch game_cost_timer_;
t3::Stopwatch rendering_cost_timer_;

bool step_update_ = false;

struct Step
{
    void operator ()( int ){
        step_update_ = true;
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
    , dmb_root_menu_( &dmf_system_, "RETURN ROOT MENU", app, &::t3::Application::gotoRootMenuScene )
    , dmb_step_( &dmf_system_, "STEP", 0 )
    , dmi_workbar_visible_( &dmf_system_, "WORKBAR VISIBLE", workbar_visible_, 1 )
    {
        t3::GameSystem::getInstance().registryDebugMenu( dmf_system_ );
    }
    
    
    t3::DebugMenuFrame& getSystemDebugMenuRoot() {
        return dmf_system_;
    };
    
    
private:
    t3::DebugMenuFrame dmf_system_;
    t3::DebugMenuButtonMethod<t3::Application> dmb_root_menu_;
    t3::DebugMenuButtonFunctor<Step> dmb_step_;
    t3::DebugMenuItem<bool> dmi_workbar_visible_;
};


namespace t3 {

Application::Application(
    SceneGenerator* root_scene_generator
)   : root_scene_generator_( root_scene_generator )
    , system_menu_(nullptr)
{
}

Application::~Application()
{
}

void Application::initializeApplication()
{
    GameSystem::createInstance();
    SceneManager::createInstance();
    DebugMenu::createInstance();
    
    
    t3::GameSystem* game_system = t3::GameSystem::getInstancePointer();
    game_system->setScreenSize( 
        ivec2_t( 
            glue::getScreenWidth(),
            glue::getScreenHeight() 
        )
    );
    SceneManager::getInstance().forceChangeScene( root_scene_generator_ );

    //  ワークバーのカラーリング設定
    cpu_bar_.setLimitWidthPixel( glue::getScreenWidth() );
    cpu_bar_.setColor( 0, COLOR_VIOLET );
    cpu_bar_.setColor( 1, COLOR_YELLOW );
    cpu_bar_.setColor( 2, COLOR_GREEN );
    cpu_bar_.setPosition( vec2_t( 1, glue::getScreenHeight() -5 ) );


    //  システムデバッグメニュー登録
    system_menu_.reset( new ApplicationDebugMenu(this) );

    DebugMenu& debug_menu_root = DebugMenu::getInstance();
    system_menu_->getSystemDebugMenuRoot().attachSelf(
        debug_menu_root.getMenuRoot()
    );
}


void Application::update( tick_t tick )
{
    system_cost_timer_.start();     // system cost 計測開始
    
    SceneManager& sm = SceneManager::getInstance();
    GameSystem& gs = GameSystem::getInstance();
    DebugMenu& dm = DebugMenu::getInstance();
    
    
    dm.update( tick );
    gs.update( tick );
    
    system_cost_timer_.end();       // system cost 計測終了
    game_cost_timer_.start();       // game cost 計測開始
    //  シーンの更新
    if ( isSuspend() ){
        //  サスペンド中
        sm.suspendScene( tick );
    }
    else {
        //  更新中
        sm.updateScene( tick );
        
        //  デバッグメニュー開く
        if ( isDebugMenuOpenRequest() ){
            dm.openMenu();
        }
    }
    game_cost_timer_.end();         // game cost 計測終了
    rendering_cost_timer_.start();         // rendering cost 計算開始
    
    //  シーン切り替わり判定
    if ( sm.isSceneChenged() ){
        //  シーンが切り替わったのでデバッグメニューを閉じる
        dm.closeMenu();
    }
    
    //  シーン描画
    beginRender();
    
    //  デバッグメニュー描画
    dm.render();
    
    rendering_cost_timer_.end();           // rendering cost 計算終了
    
    //  CPU負荷可視化
    if ( workbar_visible_ ){
        cpu_bar_.setParam( 0, system_cost_timer_.interval() );
        cpu_bar_.setParam( 1, game_cost_timer_.interval() );
        cpu_bar_.setParam( 2, rendering_cost_timer_.interval() );
/*
        t3::printDisplay( 0, 100, "%f", system_cost_timer_.interval() );
        t3::printDisplay( 0, 120, "%f", game_cost_timer_.interval() );
        t3::printDisplay( 0, 140, "%f", rendering_cost_timer_.interval() );
*/
        cpu_bar_.draw();
    }
    
    endRender();
   
}

bool Application::isDebugMenuOpenRequest(){
    const Pad& pad = debugPad();
    
    bool result = false;
    if ( pad.isPress( PAD_BUTTON_3 ) ){
        result = true;
    }
    return result;
}

bool Application::isSuspend() const {
    //  ステップ実行フック
    if ( step_update_ ){
        step_update_ = false;
        return false;
    }
    
    //  強制シーンチェンジ時もサスペンドを解く
    SceneManager& sm = SceneManager::getInstance();
    if ( sm.isForceChangeRequested() ){
        return false;
    }

    //  サスペンド中か判定
   if ( isSuspending() ){
       return true;
   }


    return false;
    
}



void Application::beginRender()
{
  
}


void Application::endRender()
{
    GameSystem& gs = GameSystem::getInstance();
    glue::setClearColor( gs.getDisplayClearColor() );
    glue::swapBuffers();
    glue::clearDisplay( GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT );    
}

void Application::gotoRootMenuScene()
{
    t3::SceneManager::getInstance().forceChangeScene( root_scene_generator_ );
}








}   // namespace t3


