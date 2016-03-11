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




///
/// コンストラクタ
Application::Application()
    : last_scene_change_frame_(0)
    , initialized_(false)
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
/// アプリケーション初期化
void Application::initializeApplication()
{
    

    //  ゲームの初期化
    //  継承先で実装
    initializeGame();

    //  ゲームの初期化initializeGameの終了までにアプリのルートシーンを
    //  設定しておく

    //  最初に起動するのはブートシーン
    auto& d = Director::instance();
    auto boot_scene = TaskGenerator<BootScene>::instancePtr();
    d.rootTask()->addTaskRequest(boot_scene);

    
    initialized_ = true;
}


///
/// アプリケーション更新
void Application::updateApplication(const DeltaTime dt) {
    
    //  シーン切り替わり判定
    auto& sm = SceneManager::instance();
    if (sm.isSceneChenged()) {
        //  シーンが切り替わったのでデバッグメニューを閉じる
        auto& dm = DebugMenu::instance();
        dm.closeMenu();
        
        uint32_t now_frame = frame_counter_.now();
        HeapManager::dumpAllocateInfo(1, now_frame);
        
        //  シーンが切り替わったタイミングを保存
        last_scene_change_frame_ = now_frame;
    }

}

///
/// アプリケーションの描画
void Application::renderApplication() {
    T3_RENDER_ASSERT();

}


///
/// 後片付け
void Application::terminateApplication() {
    //  ゲームの終了処理
    terminateGame();    
}


///
/// ルートシーンへ飛ぶ
void Application::gotoRootScene() {
    t3::SceneManager::instance().restart();
}




TRI_CORE_NS_END


