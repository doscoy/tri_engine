////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "sandbox_template.hpp"



class TemplateScene::SceneContext {

public:
    SceneContext()
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize() {

    }
    
    void terminate() {

    }
    
    void update(t3::tick_t delta_time) {
        
    }


    void suspend(t3::tick_t delta_time) {

    }

private:

};






TemplateScene::TemplateScene()
    : SceneBase( "Template" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

TemplateScene::~TemplateScene() {
    
}


void TemplateScene::initializeScene() {
    context_->initialize();
}


void TemplateScene::terminateScene() {
    context_->terminate();
}


void TemplateScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void TemplateScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















