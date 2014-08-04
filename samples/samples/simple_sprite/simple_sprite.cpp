

#include "simple_sprite.hpp"
#include <vector>


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
        t3::FilePath kani_path("stamp.png");
    
        //  ハンドルをとっておく
        tex3_handle_ = texture_manager.load(kani_path);
        
        
        for (int i = 0; i < 28; ++i) {
            addSprite();
        }
        adjustSpritesPosition();

    }
    
    void terminate(){
    }
    
    void update(t3::tick_t delta_time){

        //  現在のスプライト数表示
        auto sprites = sprite_layer_.getManagementSprites();
        t3::printDisplay(0, 0, "%d", sprites->size());
        
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
        float sin = t3::sinf(total_time_);
        sprite_opacity_ = (sin * 128) + 128;
    }

    void suspend(t3::tick_t delta_time) {
        adjustSpritesPosition();
    }

private:
    void rollingSprites() {
        auto sprites = sprite_layer_.getManagementSprites();
        if (sprites->empty()) {
            //  スプライト無し
            return;
        }
        
        int spr_idx = 0;
        for (auto spr : *sprites) {
            
            float angle = spr->transform()->rotation();
            if (spr_idx % 2) {
                spr->transform()->rotation(angle + 1);
            }
            spr_idx += 1;
        }
    }
    
    
    void fadeSprites() {
       auto sprites = sprite_layer_.getManagementSprites();
        if (sprites->empty()) {
            //  スプライト無し
            return;
        }
        
        int spr_idx = 0;
        for (auto spr : *sprites) {
            
            if ((spr_idx % 6) == 0) {
                spr->opacity(sprite_opacity_);
            }
            spr_idx += 1;
        }
    
    }

    void adjustSpritesPosition() {
        auto sprites = sprite_layer_.getManagementSprites();
        if (sprites->empty()) {
            //  スプライト無し
            return;
        }
        
        t3::SpritePtr sprite = sprites->front();
        t3::Vec2 offset = t3::Vec2(
            sprite->scaledSize().x_,
            sprite->scaledSize().y_
        );
        int x_count = t3::Director::instance().virtualScreenSize().x_ / offset.x_ -1;
        int y = 7;
        int i = 0;
        for (auto spr : *sprites) {
            if (i % x_count == 0) {
                y -= 1;
            }

            float pos_x = ((i % x_count) * offset.x_) - 300;
            float pos_y = y * offset.y_;
            spr->transform()->position(pos_x, pos_y);
            i += 1;
        }
    }
    
private:
    void addSprite() {
        t3::TextureManager& texture_manager = t3::TextureManager::instance();

        //  スプライト増やす
        std::shared_ptr<t3::Sprite> sprite = sprite_layer_.createSprite(
            texture_manager.resource(tex3_handle_)
        );
        sprite->transform()->scale(2.0f);
        
        
        t3::Director::random_t& random_gen =  t3::Director::instance().random();
        if (random_gen.getUInt(5) == 0) {
            sprite->color(t3::Color::red());
        }
        else {
            sprite->color(t3::Color::white());
        }
    }
    
    void removeSprite() {
        auto sprites = sprite_layer_.getManagementSprites();
        if (!sprites->empty()) {
            sprites->pop_back();
        }
    }


private:
    t3::UniqueID tex3_handle_;
    t3::tick_t total_time_;
    int sprite_opacity_;
    t3::SpriteLayer sprite_layer_;
};






SimpleSpriteScene::SimpleSpriteScene()
    : Scene( "SpriteTest" ) {
    context_.reset(T3_NEW SceneContext());
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
        finish(true);
    }
}

void SimpleSpriteScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















