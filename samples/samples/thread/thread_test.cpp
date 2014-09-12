

#include "thread_test.hpp"
#include <thread>

#define CHAR_NUM 20
void job() {

    for (int i = 0; i < CHAR_NUM; ++i) {
        printf("x");
    }
}


class ThreadTestScene::SceneContext {

    void jo2() {
        for (int i = 0; i < CHAR_NUM; ++i) {
            printf("w");
        }
    }


public:
    SceneContext()
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize() {
        //  スレッド生成
        std::thread th1(job);
        std::thread th2(&ThreadTestScene::SceneContext::jo2, this);
        
        
        
        
        th1.join();
        th2.join();
    }
    
    void terminate() {

    }
    
    void update(t3::tick_t delta_time) {

    }

    void suspend(t3::tick_t delta_time) {

    }

private:


};






ThreadTestScene::ThreadTestScene()
    : Scene( "ThreadTest" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

ThreadTestScene::~ThreadTestScene() {
    
}


void ThreadTestScene::initializeScene() {
    context_->initialize();
}


void ThreadTestScene::terminateScene() {
    context_->terminate();
}


void ThreadTestScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void ThreadTestScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















