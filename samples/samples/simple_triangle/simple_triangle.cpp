

#include "simple_triangle.hpp"
#include "base/tri_std.hpp"


class SimpleTriangleScene::SceneContext
{
public:
    SceneContext()
        : total_time_(0)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize(){
        
    }
    
    void terminate(){
    }
    
    void update(t3::tick_t delta_time){

  
    }

    void suspend(t3::tick_t delta_time) {

    }


private:
    t3::tick_t total_time_;
    t3::SpriteLayer sprite_layer_;
    t3::Vector<t3::SpritePtr> sprites_;
    t3::TexturePtr textures_[9];
};






SimpleSpriteScene::SimpleSpriteScene()
    : Scene( "TriangleTest" ) {
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
    
    auto& director = t3::Director::instance();
    auto& pad = director.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void SimpleSpriteScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















