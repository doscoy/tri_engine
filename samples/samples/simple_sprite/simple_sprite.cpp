

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
      
        sprite_layer_.attachSystem();
        t3::TextureManager& texture_manager = t3::TextureManager::getInstance();
        
        t3::FilePath kani_path("kani.png");
        t3::File kani_file;
        kani_file.loadFile(kani_path);
        T3_ASSERT(kani_file.isVaild());
        
        tex3_handle_ = texture_manager.load(kani_path);
        
    }
    
    void terminate(){
        sprite_layer_.detachSystem();
    }
    
    void update( t3::tick_t tick ){
 
        t3::TextureManager& texture_manager = t3::TextureManager::getInstance();
        t3::GameSystem& gs = t3::GameSystem::getInstance();
        const t3::Pad& pad = gs.getInput().getPad();
        
        //by inoue
        static float s_counter = 0.0f;
        s_counter += tick;
        float pos = 50.0f*sinf(s_counter*5.f);
        
        if ( pad.isPress( t3::Pad::BUTTON_RIGHT ) ){

            std::shared_ptr<t3::Texture> tex = texture_manager.getResource( tex3_handle_ );
            t3::Sprite* spr = sprite_layer_.createSprite( tex );
            T3_NULL_ASSERT( spr );
            T3_ASSERT( spr->isValid() );
            spr->setPosition(
                gs.getRandomNumberGenerator().getUInt(gs.getScreenSize().x_),
                0
            );
            sprites_.push_back( spr );
        }
        else if ( pad.isRepeat( t3::Pad::BUTTON_LEFT ) ){
            if ( sprites_.size() > 0 ){
                t3::Sprite* p = sprites_.back();
                p->destroy();
                sprites_.pop_back();
            }
        }
        
        for ( auto sprite : sprites_ ) {
            //by inoue
            t3::Vec2 v = sprite->getPosition();
            v.y_ = pos+200;
            sprite->setPosition(v);
            
        }

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
    context_.reset( T3_NEW SceneContext() );    
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


void SimpleSpriteScene::updateScene( t3::tick_t tick )
{
    context_->update( tick );
    
    t3::GameSystem& gs = t3::GameSystem::getInstance();
    const t3::Pad& pad = gs.getInput().getPad();
    if ( pad.isTrigger( t3::Pad::BUTTON_B ) ){
        finish_ = true;
    }   
}

