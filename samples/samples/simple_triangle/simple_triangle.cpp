

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

    void debugRender() {
        t3::drawRectangleCenterSize(
            t3::Vec2(0, 0),
            t3::Vec2(30, 30),
            t3::color_sample::cyan()
        );
    }

private:
    t3::tick_t total_time_;
    t3::SpriteLayer sprite_layer_;
    t3::Vector<t3::SpritePtr> sprites_;
    t3::TexturePtr textures_[9];
};






SimpleTriangleScene::SimpleTriangleScene()
    : Scene( "TriangleTest" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

SimpleTriangleScene::~SimpleTriangleScene() {
    
}


void SimpleTriangleScene::initializeScene() {
    context_->initialize();
}


void SimpleTriangleScene::terminateScene() {
    context_->terminate();
}


void SimpleTriangleScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    auto& director = t3::Director::instance();
    auto& pad = director.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void SimpleTriangleScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}


void SimpleTriangleScene::debugRenderScene() {
    context_->debugRender();
}













