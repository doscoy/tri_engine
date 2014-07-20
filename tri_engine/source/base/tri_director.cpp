#include "tri_director.hpp"
#include "tri_scene.hpp"
#include "util/tri_counter.hpp"
#include "kernel/tri_kernel.hpp"
#include "dbg/tri_dbg.hpp"

#include "gfx/tri_texture.hpp"

#include "audio/tri_audio_resource.hpp"
#include "geometry/tri_geometry.hpp"
#include "base/tri_system_events.hpp"




namespace t3 {

extern Counter frame_counter_;

inline namespace base {
    
const Input& Director::input(
    const int player_no
)  {
    return t3::Director::instance().input_.at(player_no);
}
    
void Director::addSystemTask(
    std::shared_ptr<Task> task
) {
    instance().task_manager_.attach(task);
}


RenderLayer* Director::findLayer(
    const std::string& layer_name
) {
    t3::RenderLayers layers = t3::Director::instance().layers();
    
    for (auto layer : layers) {
        if (layer_name == layer->name()) {
            return layer;
        }
    }
    
    return nullptr;
}

Vec2 Director::screenToViewport(
    const Vec2& screen_pos
) {
    return screen_pos / instance().getScreenSize() * 2.0f;
}

Vec2 Director::viewportToScreen(
    const Vec2& viewport_pos
) {
    return viewport_pos * instance().getScreenSize() * 0.5f;
}

bool Director::isOutOfScreen(
    const Vec2 &screen_pos
) {
    Vec2 vpos = screenToViewport(screen_pos);
    if (!inRange(vpos.x_, -1.0f, 1.0f)) {
        return true;
    }
    else if (!inRange(vpos.y_, -1.0f, 1.0f)) {
        return true;
    }
    
    return false;
}


void Director::setupBlackOut() {
    instance().fade_layer_->setupFadeParam(1, Color::black());
}

void Director::setupBlackIn() {
    instance().fade_layer_->setupFadeParam(0, Color::black());
}

void Director::fadeOut() {
    instance().fade_layer_->fadeOut(1.0f);
}

void Director::fadeIn() {
    instance().fade_layer_->fadeIn(1.0f);
}

bool Director::isFadeEnd() {
    return instance().fade_layer_->isFadeEnd();
}

bool Director::isFadeInEnd() {
    return instance().fade_layer_->isFadeInEnd();
}

bool Director::isFadeOutEnd() {
    return instance().fade_layer_->isFadeOutEnd();
}

const Vec2& Director::getScreenSize() {
    return instance().screen_size_;
}

void Director::printLog(const char* const buf) {
    if (!getInstancePointer()) {
        return;
    }

    if (!instance().log_layer_) {
        return;
    }
    instance().log_layer_->writeString(buf);
}

void Director::printDisplay(
    int x,
    int y,
    const uint32_t color,
    const int font_size,
    const char* const buf
) {
    instance().dbg_screen_layer_->writeString(x, y, color, font_size, buf);
}


// *********************************************
//  コンストラクタ
Director::Director()
    : log_layer_(nullptr)
    , dbg_screen_layer_(nullptr)
    , random_number_generator_(1)
    , screen_size_()
    , input_()
    , layers_()
    , fade_layer_(nullptr)
    , event_manager_("ev_man", true)
    , task_manager_()
    , dm_color_idx_(nullptr, "CLEAR COLOR IDX", use_clear_color_index_, 1, 0, 3)
    , use_clear_color_index_(0)
    , clear_colors_{{
        Color::black(),
        Color::darkgray(),
        Color::white(),
        Color::blue()
      }}
    , dm_random_pointing_(nullptr, "RANDOM POINTING", random_pointing_, 1)
    , random_pointing_(false)
    , dm_game_speed_(nullptr, "GAME SPEED", game_speed_, 0.1f, 0.0f, 4.0f)
    , game_speed_(1.0f)
    , dm_layers_(nullptr, "LAYERS")
    , layer_list_()
    , exit_request_(false)
    , suspend_(false)
{
    //  テクスチャマネージャ生成
    TextureManager::createInstance();
    
    //  オーディオマネージャ生成
    AudioManager::createInstance();

    //  コリジョンマネージャ生成
    CollisionManager::createInstance();
    
}

// *********************************************
//  デストラクタ
Director::~Director()
{
    CollisionManager::destroyInstance();
    AudioManager::destroyInstance();
    TextureManager::destroyInstance();
    SceneManager::destroyInstance();
}



void Director::initializeGameSystem() {
    clearColor();
    
    dm_layers_.setFocusCallback(
        this,
        &Director::registryLayersToDebugMenu
    );
    dm_layers_.setUnfocusCallback(
        this,
        &Director::unregistryLayersToDebugMenu
    );
 
    
    //  システムフェードレイヤー生成
    fade_layer_.reset(T3_NEW FadeLayer("sys-fade", RenderLayer::PRIORITY_SYS_FADE));
    
    //  デバッグ用レイヤー生成
    log_layer_.reset(T3_NEW DebugLogLayer("dbg log"));
    dbg_screen_layer_.reset(T3_NEW DebugStringLayer("dbg print"));

}


void Director::terminategameSystem() {

}

// *********************************************
//  アップデート
void Director::update(
    const tick_t delta_time
) {
    //  起動からのフレーム数カウント
    frame_counter_.up();

    //  入力更新
    updateInput(delta_time);
    
    //  タスク更新
    task_manager_.updateTask(delta_time);

    //  コリジョン判定
    CollisionManager& col_manager = CollisionManager::instance();
    col_manager.collisionDetection();
    
    //  イベントのブロードキャスト
    safeTickEventManager();
    
    
    //  終了リクエストチェック
    if (platform::isExitRequest()) {
        exit_request_ =  true;
    }
}

void Director::suspend(
    const tick_t delta_time
) {
    clearColor();
    
    //  入力更新
    updateInput(delta_time);
}


void Director::updateInput(
    const tick_t delta_time
) {
    for (int pad_idx = 0; pad_idx < MAX_PAD; ++pad_idx){
        Input& input = input_[pad_idx];
    
        //  パッド情報更新
        platform::GamePadData pad_data;
        platform::platformPadData(pad_idx, &pad_data);
        input.updatePad(pad_data, delta_time);
        
        
        //  ポインティング情報更新
        platform::PointingData point_data;
        platform::platformPointingData(
            pad_idx,
            &point_data
        );
        
        if (random_pointing_) {
            if ((frame_counter_.now() % 4) == 0) {
                point_data.hit_ = true;
                const Vec2 half = screen_size_ / 2;
                point_data.x_ = random_number_generator_.getInt(screen_size_.x_) - half.x_;
                point_data.y_ = random_number_generator_.getInt(screen_size_.y_) - half.y_;
        //        T3_TRACE("touch %f  %f\n", point_data.x_, point_data.y_);
            }
            else {
                
            }
        }
        
        input.updatePointing(
            point_data,
            delta_time
        );
        
        //  加速度センサー更新
        platform::AccelerometerData acc_data;
        platform::platformAcceleromator(pad_idx, &acc_data);
        input.updateAccelermeter(
            acc_data,
            delta_time
        );
        
        
        
        //  入力イベント発行
        const Pointing& pointing = input.pointing();
        //  トリガー
        if (pointing.isTrigger()) {
            auto eve_point_trg = std::make_shared<PointingTriggeredEvent>();
            eve_point_trg->inputNo(pad_idx);
            eve_point_trg->position(pointing.position());
            safeQueueEvent(eve_point_trg);
        }
        //  リリース
        if (pointing.isRelease()) {
            auto eve_point_rls = std::make_shared<PointingReleasedEvent>();
            eve_point_rls->inputNo(pad_idx);
            eve_point_rls->position(pointing.position());
            safeQueueEvent(eve_point_rls);
        }
        //  ムーブ
        if (pointing.isMoving()) {
            auto eve_point_move = std::make_shared<PointingMovingEvent>();
            eve_point_move->inputNo(pad_idx);
            eve_point_move->position(pointing.position());
            eve_point_move->moveDistance(pointing.moveDistance());
            safeQueueEvent(eve_point_move);
        }
    }
    
    
    
    
    
    //  debug pad
    platform::GamePadData dbg_pad_data;
    platform::platformPadData(0, &dbg_pad_data);
    uint32_t dpad_buttons = dbg_pad_data.buttonData();

    t3::DebugMenu& debug_menu = t3::DebugMenu::instance();
    const VirtualPad* vpad = debug_menu.virtualPad();
    if (vpad) {
        dpad_buttons |= vpad->getPadData()->buttonData();
    }
    updateDebugPad(dpad_buttons, delta_time);

}


void Director::clearColor()
{    
    RenderSystem::clearColor(clear_colors_[use_clear_color_index_]);
}
    
    
void Director::registryToDebugMenu( DebugMenuFrame& parent_frame )
{
    //  塗りつぶしカラーの登録
    dm_color_idx_.attachSelf(parent_frame);
    
    //  レイヤーのメニューフレーム登録
    dm_layers_.attachSelf(parent_frame);


    //  ゲームスピード登録
    dm_game_speed_.attachSelf(parent_frame);
}


void Director::attachLayer(t3::RenderLayer* layer)
{
    T3_NULL_ASSERT(layer);
//    T3_TRACE("Attach Layer %s\n", layer->name().c_str());
    layers_.push_back(layer);
    layers_.sort(
        []( RenderLayer*lhs, RenderLayer* rhs ){
            return lhs->priority() < rhs->priority();
        }
    );
}

void Director::detachLayer(t3::RenderLayer* layer)
{
//    T3_TRACE("Detach Layer %s\n", layer->name().c_str());

    layers_.remove(layer);
    layers_.sort(
        []( RenderLayer*lhs, RenderLayer* rhs ){
            return lhs->priority() < rhs->priority();
        }
    );
}


void Director::registryLayersToDebugMenu()
{
    for (auto layer: layers_) {
        layer->registryToDebugMenu(dm_layers_);
    }
}

void Director::unregistryLayersToDebugMenu()
{
    for (auto layer: layers_) {
        layer->unregistryToDebugMenu();
    }
}

void Director::showTask() const {

    task_manager_.printTask();
}





}   // inline namespace base
}   // namespace t3


