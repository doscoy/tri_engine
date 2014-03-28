

#include "simple_sprite.hpp"
#include <vector>

extern std::shared_ptr<t3::Texture> debugfont_;



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
        t3::TextureManager& texture_manager = t3::TextureManager::getInstance();
        
        t3::FilePath kani_path("stamp.png");
        t3::File kani_file;
        kani_file.loadFile(kani_path);
        T3_ASSERT(kani_file.isVaild());
        
        tex3_handle_ = texture_manager.load(kani_path);
        
        t3::Sprite* sprite = sprite_layer_.createSprite(
            texture_manager.getResource(tex3_handle_)
        );
        sprite->setPosition(t3::Vec2(130,130));
        sprites_.push_back(sprite);
    }
    
    void terminate(){
        sprite_layer_.detachSystem();
    }
    
    void update( t3::tick_t tick ){
        t3::printDisplay( 0, 0, "%d", sprites_.size() );
    }

private:
    std::vector<t3::Sprite*> sprites_;
    t3::uid_t tex3_handle_;
    
    t3::SpriteLayer sprite_layer_;
};






SimpleSpriteScene::SimpleSpriteScene()
    : Scene( "SpriteTest" )
{
    context_.reset(T3_NEW SceneContext());
}

SimpleSpriteScene::~SimpleSpriteScene()
{
    
}


void SimpleSpriteScene::initializeScene()
{
    context_->initialize();
}


void SimpleSpriteScene::terminateScene()
{
    context_->terminate();
}


void SimpleSpriteScene::updateScene(t3::tick_t tick)
{
    context_->update(tick);
    
    t3::GameSystem& gs = t3::GameSystem::getInstance();
    const t3::Pad& pad = gs.getInput().getPad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish_ = true;
    }   
}

