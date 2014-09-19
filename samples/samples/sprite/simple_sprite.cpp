

#include "simple_sprite.hpp"
#include "base/tri_std.hpp"


class SimpleSpriteScene::SceneContext
{
public:
    SceneContext()
        : total_time_(0)
        , sprite_opacity_(0)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize(){
        
        //  テクスチャ読み込み
        t3::TextureManager& texture_manager = t3::TextureManager::instance();
        t3::FilePath stamp_path("stamp.png");
        t3::FilePath ui_path("tri_engine_ui_sample.png");
    
        //  ハンドルをとっておく
        stamp_handle_ = texture_manager.load(stamp_path);
        ui_handle_ = texture_manager.load(ui_path);
        
        
        for (int i = 0; i < 28; ++i) {
            addSprite();
        }
        adjustSpritesPosition();

    }
    
    void terminate(){
    }
    
    void update(t3::tick_t delta_time){

        //  現在のスプライト数表示
        t3::printDisplay(0, 50, "%d", sprites_.size());
        
        //  画面タッチで数制御
        t3::Pointing pointing = t3::Director::instance().input().pointing();
        if (pointing.isHold()) {
        
            const t3::Point2& pointing_pos = pointing.position();
            if (pointing_pos.x_ < 0) {
                addSprite();
            }
            else {
                removeSprite();
            }
            adjustSpritesPosition();
        }
        
        rollingSprites();
        fadeSprites();
        total_time_ += delta_time;
        float sin = (t3::sinf(total_time_) + 1.0f) * 0.5f;
        
        sprite_opacity_ = (sin * 255);
        T3_ASSERT_RANGE(sprite_opacity_, 0, 255);
    }

    void suspend(t3::tick_t delta_time) {
        adjustSpritesPosition();
    }

private:
    void rollingSprites() {
        if (sprites_.empty()) {
            //  スプライト無し
            return;
        }
        
        int spr_idx = 0;
        for (auto spr : sprites_) {
            float angle = spr->transform()->rotation();
            if (spr_idx % 2) {
                spr->transform()->rotation(angle + 1);
            }
            spr_idx += 1;
        }
    }
    
    
    void fadeSprites() {

        if (sprites_.empty()) {
            //  スプライト無し
            return;
        }
        
        
        int spr_idx = 0;
        for (auto spr : sprites_) {
            if ((spr_idx % 6) == 0) {
                spr->opacity(sprite_opacity_);
            }
            spr_idx += 1;
        }
    
    }

    void adjustSpritesPosition() {
        if (sprites_.empty()) {
            //  スプライト無し
            return;
        }
        
        t3::SpritePtr spr = sprites_.front();
        
        t3::Vec2 offset = t3::Vec2(
            spr->scaledSize().x_ / 2,
            spr->scaledSize().y_
        );
        int x_count = t3::Director::instance().virtualScreenSize().x_ / offset.x_ -1;
        int y = 7;
        int i = 0;
        for (auto spr : sprites_) {
            if (i % x_count == 0) {
                y -= 1;
            }

            float pos_x = ((i % x_count) * offset.x_) - 300;
            float pos_y = y * offset.y_;
            spr->transform()->position(pos_x, pos_y);
            if (i == 52) {
                spr->priority(t3::Sprite::PRIORITY_HIGH_2);
                spr->transform()->scale(3);
            }
            i += 1;
        }
    }
    
private:
    void addSprite() {
        t3::TextureManager& texture_manager = t3::TextureManager::instance();
        t3::Director::random_t& random_gen =  t3::Director::instance().random();

        //  スプライト増やす
        t3::TexturePtr tex;
//        bool tex_type_ui = random_gen.getInt(5) == 0;
        
        bool tex_type_ui = true;
        
        if (sprites_.size() > 30 && sprites_.size() < 45) {
            tex_type_ui = false;
        }
        
        if (tex_type_ui) {
            tex = texture_manager.resource(ui_handle_);
        }
        else {
            tex = texture_manager.resource(stamp_handle_);
        }
        
        t3::SpritePtr sprite = sprite_layer_.createSprite(
            tex
        );
        sprite->transform()->scale(1.0f);
        
        
        if (tex_type_ui) {
            //  UIテクスチャが使われてる時はUVを設定
            sprite->setupTextureCoordAndSize(t3::Vec2(0, 0), t3::Vec2(64, 64));
        }
        
        
        if (random_gen.getUInt(5) == 0) {
            sprite->color(t3::Color::red());
        }
        else {
            sprite->color(t3::Color::white());
        }
        
        sprites_.push_back(sprite);
    }
    
    void removeSprite() {
        if (sprites_.empty()) {
            return;
        }
        
        sprites_.pop_back();
        
    }


private:
    t3::UniqueID stamp_handle_;
    t3::UniqueID ui_handle_;
    t3::tick_t total_time_;
    int sprite_opacity_;
    t3::SpriteLayer sprite_layer_;
    t3::Vector<t3::SpritePtr> sprites_;
};






SimpleSpriteScene::SimpleSpriteScene()
    : Scene( "SpriteTest" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

SimpleSpriteScene::~SimpleSpriteScene() {
    
}


void SimpleSpriteScene::initializeScene() {
    context_->initialize();
}


void SimpleSpriteScene::terminateScene() {
    context_->terminate();
}


void SimpleSpriteScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void SimpleSpriteScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















