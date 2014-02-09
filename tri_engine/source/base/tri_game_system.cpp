#include "tri_game_system.hpp"
#include "tri_resource_manager.hpp"
#include "tri_scene.hpp"
#include "util/tri_counter.hpp"
#include "kernel/tri_kernel.hpp"
#include "dbg/tri_dbg.hpp"



namespace t3 {

extern Counter frame_counter_;

inline namespace base {


// *********************************************
//  コンストラクタ
GameSystem::GameSystem()
    : random_number_generator_( 1 )
    , dmi_color_idx_( nullptr, "CLEAR COLOR IDX", use_clear_color_index_, 1, 0, 3 )
    , use_clear_color_index_( 0 )
    , clear_colors_{{
        Color::darkgray(),
        Color::black(),
        Color::white(),
        Color::blue()}}
    , dmf_layers_( nullptr, "LAYERS" )
    , layer_list_()
    , suspend_( false )
{
    //  テクスチャマネージャ生成
    TextureManager::createInstance();
    
    setClearColor();

    dmf_layers_.setFocusCallback(
        this,
        &GameSystem::registryLayersToDebugMenu
    );
    dmf_layers_.setUnfocusCallback(
        this,
        &GameSystem::unregistryLayersToDebugMenu
    );



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

void GameSystem::suspend( tick_t tick )
{
    setClearColor();
}

void GameSystem::setClearColor()
{
    glue::setClearColor( clear_colors_[use_clear_color_index_] );
}
    
    
void GameSystem::registryToDebugMenu( DebugMenuFrame& parent_frame )
{
    //  塗りつぶしカラーの登録
    dmi_color_idx_.attachSelf( parent_frame );
    
    //  レイヤーのメニューフレーム登録
    dmf_layers_.attachSelf( parent_frame );
}


void GameSystem::attachLayer( t3::RenderLayer& layer )
{
    T3_TRACE("Attach Layer %s\n", layer.getLayerName());
    layers_.push_back( &layer );
    layers_.sort(
        []( RenderLayer*lhs, RenderLayer* rhs ){
            return lhs->getPriority() < rhs->getPriority();
        }
    );
}

void GameSystem::detachLayer( t3::RenderLayer& layer )
{
    T3_TRACE("Detach Layer %s\n", layer.getLayerName());

    layers_.remove( &layer );
    layers_.sort(
        []( RenderLayer*lhs, RenderLayer* rhs ){
            return lhs->getPriority() < rhs->getPriority();
        }
    );
}


void GameSystem::registryLayersToDebugMenu()
{
    for (auto layer: layers_) {
        layer->registryToDebugMenu(dmf_layers_);
    }
}

void GameSystem::unregistryLayersToDebugMenu()
{
    for (auto layer: layers_) {
        layer->unregistryToDebugMenu();
    }
}





}   // inline namespace base
}   // namespace t3


