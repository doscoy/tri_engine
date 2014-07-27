

#include "simple_sprite.hpp"
#include <vector>


class SimpleSpriteScene::SceneContext
{
public:
    SceneContext()
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
        
        
        for (int i = 0; i < 744; ++i) {
            addSprite();
        }
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
            
            float angle = spr->rotation();
            if (spr_idx % 2) {
                spr->rotation(angle + 1);
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
        
        t3::Vec2 offset(20, 20);
        int x_count = t3::Director::instance().virtualScreenSize().x_ / offset.x_ -1;
        int y = 15;
        int i = 0;
        for (auto spr : *sprites) {
            if (i % x_count == 0) {
                y -= 1;
            }

            float pos_x = ((i % x_count) * offset.x_) - 300;
            float pos_y = y * offset.y_;
            spr->position(pos_x, pos_y);
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
    }
    
    void removeSprite() {
        auto sprites = sprite_layer_.getManagementSprites();
        if (!sprites->empty()) {
            sprites->pop_back();
        }
    }


private:
    t3::UniqueID tex3_handle_;
    
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
















