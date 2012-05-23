#include "tri_game_system.hpp"
#include "tri_resource_manager.hpp"
#include "tri_scene.hpp"
#include "../util/tri_counter.hpp"
#include "../io/tri_pad.hpp"
#include "../platform/platform.hpp"

namespace t3 {

extern Counter frame_counter_;

// *********************************************
//  コンストラクタ
GameSystem::GameSystem()
    : random_number_generator_( 1 )
    , suspend_( false )
{
    //  テクスチャマネージャ生成
    TextureManager::createInstance();
    
    
    
    
    
    //  デバッグ文字描画の初期化
    initializeDebugPrint();




}

// *********************************************
//  デストラクタ
GameSystem::~GameSystem()
{
    TextureManager::destroyInstance();
    SceneManager::destroyInstance();
}


// *********************************************
//  アップデート
void GameSystem::update( tick_t tick )
{
    //  起動からのフレーム数カウント
    frame_counter_.up();
    
    for ( int pad_idx = 0; pad_idx < MAX_PAD; ++pad_idx ){
        pad_[pad_idx].updatePad( glue::getPlatformPadData( pad_idx ) );
    }
    debug_pad_.updatePad( glue::getPlatformDebugPadData() );
    
    
}



  
}   // namespace t3


