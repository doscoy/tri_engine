

#include "simple_sprite.hpp"
#include "base/tri_std.hpp"


class SimpleSpriteScene::SceneContext
{
public:
    SceneContext()
        : total_time_(0)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize(){
        
        //  テクスチャ読み込み
        t3::TextureManager& texture_manager = t3::TextureManager::instance();
        t3::String stamp_path("stamp.png");
    
        //  ハンドルをとっておく
        stamp_handle_ = texture_manager.load(stamp_path);
        
        
        for (int i = 0; i < 28; ++i) {
            addSprite();
        }
        adjustSpritesPosition();

    }
    
    void terminate(){
    }
    
    void update(t3::tick_t delta_time){

        //  現在のスプライト数表示
        t3::printDisplay(400, 0, "%d", sprites_.size());
        
        //  画面タッチで数制御
        t3::Pointing pointing = t3::Director::instance().input().pointing();
        if (pointing.isHold()) {
        
            const t3::Point2& pointing_pos = pointing.position();
            if (pointing_pos.x_ < 0) {
                addSprite();
                addSprite();
                addSprite();
                addSprite();
                addSprite();
            }
            else {
                removeSprite();
            }
            adjustSpritesPosition();
        }
        
        rollingSprites();
        
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
        
        for (auto spr : sprites_) {
            float angle = spr->transform()->rotation();
            spr->transform()->rotation(angle + 1);
        }
    }
    
    void adjustSpritesPosition() {
        if (sprites_.empty()) {
            //  スプライト無し
            return;
        }
        
        t3::SpritePtr spr = sprites_.front();
        
        t3::Vec2 offset = t3::Vec2(
            spr->scaledSize().x_,
            spr->scaledSize().y_
        );
        const t3::Vec2& screen_size = t3::Director::instance().virtualScreenSize();
        
        int x_count = screen_size.x_ / offset.x_ -1;
        int y_start = 16;
        int limit_y = -(screen_size.y_ / offset.y_) + y_start +2;
        int y = y_start;
        int i = 0;
        for (auto& spr : sprites_) {
            if (i % x_count == 0 && i != 0) {
                y -= 1;
                if (y < limit_y) {
                    y = y_start;
                }
            }

            float pos_x = ((i % x_count) * offset.x_) - (screen_size.x_ / 2);
            float pos_y = y * offset.y_;
            spr->transform()->position(pos_x, pos_y);
            
            i += 1;
        }
    }
    
private:
    void addSprite() {
        t3::TextureManager& texture_manager = t3::TextureManager::instance();

        //  スプライト増やす
        const auto& tex = texture_manager.resource(stamp_handle_);
        auto sprite = sprite_layer_.createSprite(tex);
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
    t3::tick_t total_time_;
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
















