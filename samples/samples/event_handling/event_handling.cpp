

#include "event_handling.hpp"



class EventAAA
    : public t3::EventBase
{
public:
    static const t3::EventType TYPE;
    const t3::EventType& eventType() const {
        return TYPE;
    }
    
    explicit EventAAA()
        : hp_(300)
    {
    }
    
    ~EventAAA() {
    }

    int hp_;
};


class EventBBB
    : public t3::EventBase
{
public:
    static const t3::EventType TYPE;
    const t3::EventType& eventType() const {
        return TYPE;
    }
    
    explicit EventBBB()
    : hp_(234)
    {
    }
    
    ~EventBBB() {
    }
    
    int hp_;
};

const t3::EventType EventAAA::TYPE("aaa");
const t3::EventType EventBBB::TYPE("bbb");



class HpText
{
public:
    HpText(){

    }
    ~HpText(){

    }
    
public:
    
    void handleEvent(const t3::EventPtr event) {
    
        const auto aaa = static_cast<const EventAAA*>(event.get());
    
    
    }
    
    void krif(const t3::EventPtr event) {

    }
};


class EventHandlingScene::SceneContext {

public:
    SceneContext()
        : hp_text_(T3_SYS_NEW HpText)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize(){
        t3::EventManager::addListener<HpText>(hp_text_, &HpText::krif, EventAAA::TYPE);
        t3::EventManager::addListener<HpText>(hp_text_, &HpText::krif, EventBBB::TYPE);
    }
    
    void terminate(){
        t3::EventManager::removeListener(hp_text_);
    }
    
    void update(t3::tick_t delta_time){
        t3::Director& d = t3::Director::instance();
        const t3::Input& input = d.input();
        if (input.pointing().isTrigger()) {
            //  画面をタッチした
            if (d.random().getBool()){

            }
            else {

                
            }
        }
    }

    void suspend(t3::tick_t delta_time) {
    
    }

    
private:


private:
    HpText* hp_text_;
};






EventHandlingScene::EventHandlingScene()
    : SceneBase( "EventHandling" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

EventHandlingScene::~EventHandlingScene() {
    
}


void EventHandlingScene::initializeScene() {
    context_->initialize();
}


void EventHandlingScene::terminateScene() {
    context_->terminate();
}


void EventHandlingScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void EventHandlingScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















