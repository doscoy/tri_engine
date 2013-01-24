#include "tri_game_system.hpp"
#include "tri_resource_manager.hpp"
#include "tri_scene.hpp"
#include "../util/tri_counter.hpp"
#include "../io/tri_pad.hpp"
#include "../platform/platform.hpp"
#include "../dbg/tri_debugpad.hpp"



namespace t3 {

extern Counter frame_counter_;

// *********************************************
//  コンストラクタ
GameSystem::GameSystem()
    : random_number_generator_( 1 )
    , dmf_color_idx_( nullptr, "CLEAR COLOR IDX", use_clear_color_index_, 1, 0, 3 )
    , use_clear_color_index_( 0 )
    , clear_colors_{{
        COLOR_DARKGRAY,
        COLOR_BLACK,
        COLOR_WHITE,
        COLOR_BLUE}}
    , suspend_( false )
{
    //  テクスチャマネージャ生成
    TextureManager::createInstance();
    
    





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
        pad_[pad_idx].updatePad( glue::getPlatformPadData( pad_idx ), tick );
    }
    updateDebugPad( glue::getPlatformDebugPadData(), tick );
    
    
}

const Color& GameSystem::getDisplayClearColor() const
{
        
    return clear_colors_[use_clear_color_index_];
}
    
    
void GameSystem::registryDebugMenu( DebugMenuFrame& parent_frame )
{
    dmf_color_idx_.attachSelf( parent_frame );
}


void GameSystem::attachLayer( t3::RenderLayer& layer )
{
    layers_.push_back( &layer );
    layers_.sort(
        []( RenderLayer*lhs, RenderLayer* rhs ){
            return lhs->getPriority() < rhs->getPriority();
        }
    );
}

void GameSystem::detachLayer( t3::RenderLayer& layer )
{
    layers_.remove( &layer );
    layers_.sort(
        []( RenderLayer*lhs, RenderLayer* rhs ){
            return lhs->getPriority() < rhs->getPriority();
        }
    );
}












}   // namespace t3


