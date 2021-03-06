////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

//  include
#include "core/base/tri_director.hpp"
#include "core/base/tri_scene.hpp"
#include "core/utility/tri_counter.hpp"
#include "core/kernel/tri_kernel.hpp"
#include "core/debug/tri_dbg.hpp"
#include "core/graphics/tri_texture.hpp"
#include "core/audio/tri_audio_resource.hpp"
#include "core/geometry/tri_geometry.hpp"
#include "core/base/tri_system_events.hpp"
#include "../debug/tri_debug_font_data.cpp"
#include "core/base/tri_screen_manager.hpp"



TRI_CORE_NS_BEGIN

//  起動からのフレーム数カウンター
extern Counter frame_counter_;


///
/// インプットデータ取得
const Input& Director::input(
    const int player_no
)  {
    return input_.at(player_no);
}


///
/// レイヤを検索
LayerBase* Director::findLayer(
    const String& layer_name
) {
    
    for (auto layer : layers_) {
        if (layer_name == layer->name()) {
            return layer;
        }
    }
    
    return nullptr;
}

///
/// フェードレイヤーをブラックアウト用に設定
void Director::setupBlackOut() {
    fade_layer_->setupFadeParam(1, color_sample::black());
}

///
/// フェードレイヤーをブラックイン用に設定
void Director::setupBlackIn() {
    fade_layer_->setupFadeParam(0, color_sample::black());
}

///
/// フェード
void Director::fadeOut() {
    fade_layer_->fadeOut(1.0f);
}

void Director::fadeIn() {
    fade_layer_->fadeIn(1.0f);
}

bool Director::isFadeEnd() {
    return fade_layer_->isFadeEnd();
}

bool Director::isFadeInEnd() {
    return fade_layer_->isFadeInEnd();
}

bool Director::isFadeOutEnd() {
    return fade_layer_->isFadeOutEnd();
}


void Director::printDisplay(
    const float x,
    const float y,
    const uint32_t color,
    const int font_size,
    const char* const str
) {
    dbg_print_buffer_->addString(x, y, color, font_size, str);
}


const Color& Director::getClearColor() {
    return clear_colors_[use_clear_color_index_];
}

void Director::setClearColor(const Color& c) {
    clear_colors_[0] = c;
}



//  コンストラクタ
Director::Director()
    : dbg_print_layer_(nullptr)
    , dbg_print_buffer_(nullptr)
    , fade_layer_(nullptr)
    , random_number_generator_(1)    
    , input_()
    , layers_()
    , final_surface_()
    , final_layer_()
    , root_task_()
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
{
    //  ルートタスク生成
    root_task_.reset(T3_NEW TaskGroup());
    root_task_->pauseLevel(t3::PauseLevel::PAUSE_NONE);
    
    
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
    
    //  イベントマネージャ初期化
    EventManager::initialize();
    
    //  スクリーンマネージャ生成
    ScreenManager::createInstance();
    
    
    //  クリアカラー設定
	clear_colors_[0] = color_sample::darkgray();
	clear_colors_[1] = color_sample::green();
	clear_colors_[2] = color_sample::white();
	clear_colors_[3] = color_sample::blue();

    
#if TRI_DEVFLAG_AGING_CHECK
    random_pointing_ = true;
#endif
    
}


//  デストラクタ
Director::~Director() {
    
    ScreenManager::destroyInstance();
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
    fade_layer_.reset(T3_SYS_NEW FadeLayer("sys-fade", LayerBase::Priority::SYS_FADE));
    
    //  デバッグ用レイヤー生成
    dbg_print_layer_.reset(T3_SYS_NEW SpriteLayer("dbg print"));
    dbg_print_buffer_.reset(T3_SYS_NEW DebugStringBuffer());

    dbg_print_layer_->setPreUpdateCallback(
        this, 
        &Director::prepareDebugPrintFontSprites
    );

    //  デバッグ用フォントシート作成
    dbg_font_sheet_ = Texture::create(
        String("debugfont"),
        dbg_font_.width_,
        dbg_font_.height_,
        cross::RenderSystem::ColorFormat::LUMINANCE_ALPHA,
        cross::RenderSystem::TypeFormat::UNSIGNED_BYTE,
        (uint8_t*)dbg_font_.pixel_data_
    );
    
}


void Director::terminateDirector() {


    dbg_print_layer_.reset();
    dbg_print_buffer_.reset();
    dbg_font_sheet_.reset();
    fade_layer_.reset();

    root_task_.reset();

}


//  最終レイヤの設定
void Director::setupFinalLayer() {

    auto& screen_mgr = ScreenManager::instance();
    const Vec2& virtual_screen_to_device_ratio = screen_mgr.screenRevise();
    
    
    //  最終描画用レイヤー
    final_layer_.reset(T3_SYS_NEW CinemaLayer(
        Vec2(-virtual_screen_to_device_ratio.x_,-virtual_screen_to_device_ratio.y_),
        Vec2(virtual_screen_to_device_ratio.x_, virtual_screen_to_device_ratio.y_),
        "final", t3::LayerBase::Priority::SYS_FRONT
    ));
    final_surface_.reset(T3_SYS_NEW FrameBufferSurface(ScreenManager::VIRTUAL_SCREEN_WIDTH, ScreenManager::VIRTUAL_SCREEN_HEIGHT, Surface::Type::COLOR_DEPTH));
    final_layer_->texture(final_surface_->colorTexture());

    device_surface_.reset(T3_SYS_NEW DeviceSurface());

    //  最終描画用レイヤーの描画先はデバイスサーフェス
    final_layer_->renderTarget(device_surface_.get());
}

//  アップデート
void Director::update(
    const DeltaTime delta_time
) {
    //  起動からのフレーム数カウント
    frame_counter_.countup();

    //  入力更新
    updateInput(delta_time);

    
    //  タスク更新
    root_task_->doTaskUpdate(delta_time);

    //  コリジョン判定
    CollisionManager& col_manager = CollisionManager::instance();
    col_manager.collisionDetection();
    
    //  デバッグメニューの更新
    auto& dm = DebugMenu::instance();
    dm.update(delta_time);
    
    
    //  イベントのブロードキャスト
    EventManager::broadCast(delta_time);
    
    //  レイヤーの更新
    LayerBase::updateLayers(layers(), delta_time);

    
    //  終了リクエストチェック
    if (cross::isExitRequest()) {
        exit_request_ =  true;
    }
}

  
///
/// 入力情報更新
void Director::updateInput(
    const DeltaTime delta_time
) {
    auto& screen_mgr = ScreenManager::instance();


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
                const Vec2& screen_size = screen_mgr.virtualScreenSize();
                const Vec2 half = screen_size / 2;
                point_data.x_ = random_number_generator_.getInt(static_cast<int>(screen_size.x_)) - half.x_;
                point_data.y_ = random_number_generator_.getInt(static_cast<int>(screen_size.y_)) - half.y_;
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
            auto eve_point_trg = std::make_shared<event::PointingTriggeredEvent>();
            eve_point_trg->inputNo(pad_idx);
            eve_point_trg->position(pointing.position());
            EventManager::queueEvent(eve_point_trg);
        }
        //  リリース
        if (pointing.isRelease()) {
            auto eve_point_rls = std::make_shared<event::PointingReleasedEvent>();
            eve_point_rls->inputNo(pad_idx);
            eve_point_rls->position(pointing.position());
            EventManager::queueEvent(eve_point_rls);
        }
        //  ムーブ
        if (pointing.isMoving()) {
            auto eve_point_move = std::make_shared<event::PointingMovingEvent>();
            eve_point_move->inputNo(pad_idx);
            eve_point_move->position(pointing.position());
            eve_point_move->moveDistance(pointing.moveDistance());
            EventManager::queueEvent(eve_point_move);
        }
        //  フリック
        if (pointing.isFlick()) {
            auto eve_point_flick = std::make_shared<event::PointingFlickEvent>();
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

///
/// デバッグ文字用のスプライトを全リセット
void Director::prepareDebugPrintFontSprites() {

    //  前のフレームで作ったスプライトは全て削除
    dbg_print_layer_->disableAllSprites();

    while (!dbg_print_buffer_->empty()) {
        //  末尾の文字を取り出す
        auto& item = dbg_print_buffer_->back();
        dbg_print_buffer_->pop_back();

        //  スプライト生成
        auto font = dbg_print_layer_->createSprite(dbg_font_sheet_);
        font->size(item.size_);
        font->transform()->position(item.x_, item.y_);
        


        //  UV設定
        char char_idx = item.character_ - '!' + 1;
        constexpr int font_size = 8;
        int width_num = dbg_font_sheet_->width() / font_size;
        int tex_x = (char_idx % width_num) * font_size;
        int tex_y = (char_idx / width_num) * font_size;
    
        float dbg_font_tex_width = static_cast<float>(dbg_font_sheet_->width());
        float dbg_font_tex_height = static_cast<float>(dbg_font_sheet_->height());
    
        float u0 = static_cast<float>(tex_x) / dbg_font_tex_width;
        float v0 = static_cast<float>(tex_y) / dbg_font_tex_height;
    
        float u1 = static_cast<float>(tex_x + font_size) / dbg_font_tex_width;
        float v1 = static_cast<float>(tex_y + font_size) / dbg_font_tex_height;
    
        font->textureCoord(u0, v0, u1, v1);
    }
}

///
/// デバッグメニューを登録
void Director::registryToDebugMenu( 
    DebugMenuFrame& parent_frame
) {
    //  塗りつぶしカラーの登録
    dm_color_idx_.attachSelf(&parent_frame);
    
    //  レイヤーのメニューフレーム登録
    dm_layers_.attachSelf(&parent_frame);


    //  ゲームスピード登録
    dm_game_speed_.attachSelf(&parent_frame);
}


///
/// レイヤーを登録する
void Director::attachLayer(
    LayerBase* layer
) {
    T3_NULL_ASSERT(layer);
    layers_.push_back(layer);
    sortLayers();
}

///
/// レイヤーを外す
void Director::detachLayer(
    LayerBase* layer
) {
    layers_.remove(layer);
    sortLayers();
}


///
/// レイヤーをソート
/// プライオリティ順にならべかえる
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

}


TRI_CORE_NS_END


