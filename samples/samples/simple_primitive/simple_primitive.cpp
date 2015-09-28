////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "simple_primitive.hpp"


class SimplePrimitiveScene::SceneContext
{
public:
    SceneContext()
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

};






SimplePrimitiveScene::SimplePrimitiveScene()
    : SceneBase("PrimitiveTest") {
    context_.reset(T3_SYS_NEW SceneContext());
}

SimplePrimitiveScene::~SimplePrimitiveScene() {
    
}


void SimplePrimitiveScene::initializeScene() {
    context_->initialize();
}


void SimplePrimitiveScene::terminateScene() {
    context_->terminate();
}


void SimplePrimitiveScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    auto& director = t3::Director::instance();
    auto& pad = director.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void SimplePrimitiveScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}


void SimplePrimitiveScene::debugRenderScene() {
    context_->debugRender();
}













