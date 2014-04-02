

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
        //  スプライトレイヤー登録
        sprite_layer_.attachSystem();
        
        //  テクスチャ読み込み
        t3::TextureManager& texture_manager = t3::TextureManager::getInstance();
        t3::FilePath kani_path("stamp.png");
    
        //  ハンドルをとっておく
        tex3_handle_ = texture_manager.load(kani_path);
    }
    
    void terminate(){
        //  スプライトレイヤー登録解除
        sprite_layer_.detachSystem();
    }
    
    void update(t3::tick_t delta_time){

        //  現在のスプライト数表示
        auto sprites = sprite_layer_.getManagementSprites();
        t3::printDisplay(0, 0, "%d", sprites->size());
        
        //  画面タッチで数制御
        t3::Pointing pointing = t3::GameSystem::getInstance().getInput().getPointing();
        if (pointing.isHold()) {
        
            const t3::Point2& pointing_pos = pointing.getPosition();
            if (pointing_pos.x_ < t3::GameSystem::getInstance().getScreenSize().x_ / 2) {
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
        
        for (auto spr : *sprites) {
            spr->addRotationZ(1.5f);
        }
    }

    void adjustSpritesPosition() {
        auto sprites = sprite_layer_.getManagementSprites();
        if (sprites->empty()) {
            //  スプライト無し
            return;
        }
        
        auto& size = sprites->front()->getSize();
        t3::Vec2 offset(32, 32);
        int x_count = t3::GameSystem::getInstance().getScreenSize().x_ / size.x_ -1;
        int y = 0;
        int i = 0;
        for (auto spr : *sprites) {
            if (i % x_count == 0) {
                y += 1;
            }

            float pos_x = (i % x_count) * size.x_ + offset.x_;
            float pos_y = y * size.y_ + offset.y_;
            spr->setPosition(pos_x, pos_y);
            i += 1;
        }
    }
    
private:
    void addSprite() {
        t3::TextureManager& texture_manager = t3::TextureManager::getInstance();

        //  スプライト増やす
        std::shared_ptr<t3::Sprite> sprite = sprite_layer_.createSprite(
            texture_manager.getResource(tex3_handle_)
        );
    }
    
    void removeSprite() {
        auto sprites = sprite_layer_.getManagementSprites();
        if (!sprites->empty()) {
            sprites->pop_back();
        }
    }


private:
    t3::uid_t tex3_handle_;
    
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
    
    t3::GameSystem& gs = t3::GameSystem::getInstance();
    const t3::Pad& pad = gs.getInput().getPad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish_ = true;
    }
}

void SimpleSpriteScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















