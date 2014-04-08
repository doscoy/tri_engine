#include "tri_game_system.hpp"
#include "tri_scene.hpp"
#include "util/tri_counter.hpp"
#include "kernel/tri_kernel.hpp"
#include "dbg/tri_dbg.hpp"

#include "gfx/tri_texture.hpp"
#include "audio/tri_audio_resource.hpp"

namespace t3 {

extern Counter frame_counter_;

inline namespace base {


// *********************************************
//  コンストラクタ
GameSystem::GameSystem()
    : random_number_generator_(1)
    , dmi_color_idx_(nullptr, "CLEAR COLOR IDX", use_clear_color_index_, 1, 0, 3)
    , use_clear_color_index_(0)
    , clear_colors_{{
        Color::darkgray(),
        Color::black(),
        Color::white(),
        Color::blue()}}
    , dmf_layers_(nullptr, "LAYERS")
    , layer_list_()
    , exit_request_(false)
    , suspend_(false)
{
    //  テクスチャマネージャ生成
    TextureManager::createInstance();
    
    //  オーディオマネージャ生成
    AudioManager::createInstance();

}

// *********************************************
//  デストラクタ
GameSystem::~GameSystem()
{
    AudioManager::destroyInstance();
    TextureManager::destroyInstance();
    SceneManager::destroyInstance();
}

void GameSystem::initializeGameSystem() {
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
//  アップデート
void GameSystem::update( tick_t delta_time )
{
    //  起動からのフレーム数カウント
    frame_counter_.up();
    
    for (int pad_idx = 0; pad_idx < MAX_PAD; ++pad_idx){
        Input& input = input_[pad_idx];
    
        //  パッド情報更新
        platform::GamePadData pad_data;
        platform::getPlatformPadData(pad_idx, &pad_data);
        input.updatePad(pad_data, delta_time);
        
        
        //  ポインティング情報更新
        platform::PointingData point_data;
        platform::getPlatformPointingData(
            pad_idx,
            &point_data
        );
        input.updatePointing(
            point_data,
            delta_time
        );
        
        //  加速度センサー更新
        platform::AccelerometerData acc_data;
        platform::getPlatformAcceleData(pad_idx, &acc_data);
        input.updateAccelermeter(
            acc_data,
            delta_time
        );
    }
    
    //  debug pad
    platform::GamePadData dbg_pad_data;
    platform::getPlatformPadData(0, &dbg_pad_data);
    uint32_t dpad_buttons = dbg_pad_data.getButtonData();

    t3::DebugMenu& debug_menu = t3::DebugMenu::getInstance();
    const VirtualPad* vpad = debug_menu.getVirtualPad();
    if (vpad) {
        dpad_buttons |= vpad->getPadData()->getButtonData();
    }
    updateDebugPad(dpad_buttons, delta_time);
    
    
    //  終了リクエストチェック
    if (platform::isExitRequest()) {
        exit_request_ =  true;
    }
}

void GameSystem::suspend( tick_t delta_time )
{
    setClearColor();
}

void GameSystem::setClearColor()
{    
    RenderSystem::setClearColor(clear_colors_[use_clear_color_index_]);
}
    
    
void GameSystem::registryToDebugMenu( DebugMenuFrame& parent_frame )
{
    //  塗りつぶしカラーの登録
    dmi_color_idx_.attachSelf( parent_frame );
    
    //  レイヤーのメニューフレーム登録
    dmf_layers_.attachSelf( parent_frame );
}


void GameSystem::attachLayer(t3::RenderLayer* layer)
{
    T3_NULL_ASSERT(layer);
    T3_TRACE("Attach Layer %s\n", layer->getLayerName());
    layers_.push_back(layer);
    layers_.sort(
        []( RenderLayer*lhs, RenderLayer* rhs ){
            return lhs->getPriority() < rhs->getPriority();
        }
    );
}

void GameSystem::detachLayer(t3::RenderLayer* layer)
{
    T3_TRACE("Detach Layer %s\n", layer->getLayerName());

    layers_.remove(layer);
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


