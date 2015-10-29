////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "web_notification_test.hpp"



class WebNotificationTest::SceneContext {

public:
    SceneContext()
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize() {
        cm_.initialize("http://www.yahoo.co.jp");
    }
    
    void terminate() {

    }
    
    void update(t3::DeltaTime delta_time) {
        
    }


private:
    t3::cross::WebNotificationScreen cm_;
};






WebNotificationTest::WebNotificationTest()
    : SceneBase( "Template" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

WebNotificationTest::~WebNotificationTest() {
    
}


void WebNotificationTest::initializeScene() {
    context_->initialize();
}


void WebNotificationTest::terminateScene() {
    context_->terminate();
}


void WebNotificationTest::updateScene(t3::DeltaTime delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

















