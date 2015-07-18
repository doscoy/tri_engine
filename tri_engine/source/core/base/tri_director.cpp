#include "core/base/tri_director.hpp"
#include "core/base/tri_scene.hpp"
#include "core/utility/tri_counter.hpp"
#include "core/kernel/tri_kernel.hpp"
#include "core/debug/tri_dbg.hpp"

#include "core/graphics/tri_texture.hpp"

#include "core/audio/tri_audio_resource.hpp"
#include "core/geometry/tri_geometry.hpp"
#include "core/base/tri_system_events.hpp"




TRI_CORE_NS_BEGIN


extern Counter frame_counter_;


    
const Input& Director::input(
    const int player_no
)  {
    return Director::instance().input_.at(player_no);
}
    
void Director::addSystemTask(
    SharedPtr<Task> task
) {
    instance().task_manager_.attach(task);
}


LayerBase* Director::findLayer(
    const String& layer_name
) {
    Layers layers = Director::instance().layers();
    
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
    return screen_pos / instance().virtualScreenSize() * 2.0f;
}

Vec2 Director::viewportToScreen(
    const Vec2& viewport_pos
) {
    return viewport_pos * instance().virtualScreenSize() * 0.5f;
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
    instance().fade_layer_->setupFadeParam(1, color_sample::black());
}

void Director::setupBlackIn() {
    instance().fade_layer_->setupFadeParam(0, color_sample::black());
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

const Vec2& Director::screenSize() {
    return instance().virtualScreenSize();
}

void Director::printLog(const char* const buf) {
    if (!isCreatedInstance()) {
        return;
    }

    if (!instance().log_layer_) {
        return;
    }
    instance().log_layer_->writeString(buf);
}

void Director::printDisplay(
    const float x,
    const float y,
    const uint32_t color,
    const int font_size,
    const char* const str
) {
    instance().dbg_print_buffer_->addString(x, y, color, font_size, str);
}


const Color& Director::getClearColor() {
    return instance().clear_colors_[instance().use_clear_color_index_];
}

void Director::setClearColor(const Color& c) {
    instance().clear_colors_[0] = c;
}



//  コンストラクタ
Director::Director()
    : log_layer_(nullptr)
    , dbg_screen_layer_(nullptr)
    , random_number_generator_(1)
    , virtual_screen_size_(
        VIRTUAL_SCREEN_WIDTH,
        VIRTUAL_SCREEN_HEIGHT)
    , device_screen_size_(640.0f, 1136.0f)
    , input_()
    , layers_()
    , fade_layer_(nullptr)
    , task_manager_()
    , dm_color_idx_(nullptr, "CLEAR COLOR IDX", use_clear_color_index_, 1, 0, 3)
    , use_clear_color_index_(0)
    , clear_colors_()
    , dm_random_pointing_(nullptr, "RANDOM POINTING", random_pointing_)
    , random_pointing_(false)
    , dm_game_speed_(nullptr, "GAME SPEED", game_speed_, 0.1f, 0.0f, 4.0f)
    , game_speed_(1.0f)
    , dm_layers_(nullptr, "LAYERS")
    , layer_list_()
    , exit_request_(false)
    , suspend_(false)
{
    //  ファイルシステムベースパス設定
    FilePath::setBaseDirectory(cross::getDeviceFilePath());

    //  デバッグメニュー生成
    DebugMenu::createInstance();

    //  テクスチャマネージャ生成
    TextureManager::createInstance();
    
    //  オーディオマネージャ生成
    AudioManager::createInstance();

    //  コリジョンマネージャ生成
    CollisionManager::createInstance();
    
    //  シーンマネージャ生成
    SceneManager::createInstance();

	clear_colors_[0] = color_sample::darkgray();
	clear_colors_[1] = color_sample::green();
	clear_colors_[2] = color_sample::white();
	clear_colors_[3] = color_sample::blue();


#if TRI_DEVFLAG_AGING_CHECK
    random_pointing_ = true;
#endif
    
}


//  デストラクタ
Director::~Director()
{
    SceneManager::destroyInstance();
    CollisionManager::destroyInstance();
    AudioManager::destroyInstance();
    TextureManager::destroyInstance();
    DebugMenu::destroyInstance();
    
}



void Director::initializeDirector() {
    
    DebugMenu::instance().initialize();
    
    
    dm_layers_.setFocusCallback(
        this,
        &Director::registryLayersToDebugMenu
    );
    dm_layers_.setUnfocusCallback(
        this,
        &Director::unregistryLayersToDebugMenu
    );
 
    
    //  システムフェードレイヤー生成
    fade_layer_.reset(T3_SYS_NEW FadeLayer("sys-fade", LayerBase::PRIORITY_SYS_FADE));
    
    //  デバッグ用レイヤー生成
    log_layer_.reset(T3_SYS_NEW DebugLogLayer("dbg log"));
    dbg_screen_layer_.reset(T3_SYS_NEW DebugStringLayer("dbg print"));
    dbg_print_layer_.reset(T3_SYS_NEW SpriteLayer("dbg print"));
    dbg_print_buffer_.reset(T3_SYS_NEW DebugStringBuffer());

    dbg_print_layer_->setPreUpdateCallback(
        this, 
        &Director::prepareDebugPrintFontSprites
    );
}


void Director::terminateDirector() {
    dbg_screen_layer_.reset();
    log_layer_.reset();
    fade_layer_.reset();
}


//  アップデート
void Director::update(
    const tick_t delta_time
) {
    //  起動からのフレーム数カウント
    frame_counter_.countup();

    //  入力更新
    updateInput(delta_time);


    auto& sm = SceneManager::instance();
    sm.updateScene(delta_time);
    
    //  タスク更新
    task_manager_.updateTask(delta_time);

    //  コリジョン判定
    CollisionManager& col_manager = CollisionManager::instance();
    col_manager.collisionDetection();
    
    
    auto& dm = DebugMenu::instance();
    dm.update(delta_time);
    
    
    //  イベントのブロードキャスト
    EventManager::broadCast();
    
    //  レイヤーの更新
    LayerBase::updateLayers(layers(), delta_time);

    
    //  終了リクエストチェック
    if (cross::isExitRequest()) {
        exit_request_ =  true;
    }
}

  

void Director::updateInput(
    const tick_t delta_time
) {
    for (int pad_idx = 0; pad_idx < MAX_PAD; ++pad_idx){
        Input& input = input_[pad_idx];
    
        //  パッド情報更新
        cross::GamePadData pad_data;
        cross::platformPadData(pad_idx, &pad_data);
        input.updatePad(pad_data, delta_time);
        
        
        //  ポインティング情報更新
        cross::PointingData point_data;
        cross::platformPointingData(
            pad_idx,
            &point_data
        );
        
        if (random_pointing_) {
            if ((frame_counter_.now() % 4) == 0) {
                point_data.hit_ = true;
                const Vec2& screen_size = virtualScreenSize();
                const Vec2 half = screen_size / 2;
                point_data.x_ = random_number_generator_.getInt(static_cast<int>(screen_size.x_)) - half.x_;
                point_data.y_ = random_number_generator_.getInt(static_cast<int>(screen_size.y_)) - half.y_;
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
        cross::AccelerometerData acc_data;
        cross::accelerometerRead(pad_idx, &acc_data);
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
            EventManager::queueEvent(eve_point_trg);
        }
        //  リリース
        if (pointing.isRelease()) {
            auto eve_point_rls = std::make_shared<PointingReleasedEvent>();
            eve_point_rls->inputNo(pad_idx);
            eve_point_rls->position(pointing.position());
            EventManager::queueEvent(eve_point_rls);
        }
        //  ムーブ
        if (pointing.isMoving()) {
            auto eve_point_move = std::make_shared<PointingMovingEvent>();
            eve_point_move->inputNo(pad_idx);
            eve_point_move->position(pointing.position());
            eve_point_move->moveDistance(pointing.moveDistance());
            EventManager::queueEvent(eve_point_move);
        }
        //  フリック
        if (pointing.isFlick()) {
            auto eve_point_flick = std::make_shared<PointingFlickEvent>();
            eve_point_flick->inputNo(pad_idx);
            eve_point_flick->flickDirection(pointing.flickDirection());
            eve_point_flick->flickMoveOffset(pointing.flickMoveOffset());
            EventManager::queueEvent(eve_point_flick);
        }
        
    }
    
    
    
    
    
    //  debug pad
    cross::GamePadData dbg_pad_data;
    cross::platformPadData(1, &dbg_pad_data);

    auto& debug_menu = DebugMenu::instance();
    const auto& vpad = debug_menu.virtualPad();
    updateDebugPad(*vpad->getPadData(), delta_time);

}

void Director::prepareDebugPrintFontSprites() {


    dbg_print_layer_->disableAllSprites();

    while (!dbg_print_buffer_->empty()) {
        //  末尾の文字を取り出す
        auto& item = dbg_print_buffer_->back();
        dbg_print_buffer_->pop_back();
    }
}
    
    
void Director::registryToDebugMenu( 
    DebugMenuFrame& parent_frame
) {
    //  塗りつぶしカラーの登録
    dm_color_idx_.attachSelf(parent_frame);
    
    //  レイヤーのメニューフレーム登録
    dm_layers_.attachSelf(parent_frame);


    //  ゲームスピード登録
    dm_game_speed_.attachSelf(parent_frame);
}


void Director::attachLayer(LayerBase* layer)
{
    T3_NULL_ASSERT(layer);
    layers_.push_back(layer);
    sortLayers();
    

}

void Director::detachLayer(LayerBase* layer)
{
    layers_.remove(layer);
    sortLayers();
}

void Director::sortLayers() {
    layers_.sort(
        [](LayerBase*lhs, LayerBase* rhs) {
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

void Director::calcScreenRevise() {

    screen_revise_ = virtual_screen_size_ / device_screen_size_;
}

TRI_CORE_NS_END


