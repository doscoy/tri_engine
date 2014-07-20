

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
        T3_TRACE("HpText ctr\n");
    }
    ~HpText(){
        T3_TRACE("HpText dtr\n");
    }
    
public:
    
    void handleEvent(const t3::Event& event) {
    
        const EventAAA& aaa = static_cast<const EventAAA&>(event);
    
        T3_TRACE("aaa hp %d\n", aaa.hp_);
    
    }
    
    void krif(const t3::Event& event) {
        T3_TRACE("kriffff\n");
    }
};


class EventHandlingScene::SceneContext {

public:
    SceneContext()
        : hp_text_(new HpText)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize(){
        t3::safeAddListener(hp_text_, &HpText::krif, EventAAA::TYPE);
        t3::safeAddListener(hp_text_, &HpText::krif, EventBBB::TYPE);
    }
    
    void terminate(){
        t3::safeRemoveListener(hp_text_);
    }
    
    void update(t3::tick_t delta_time){
        t3::Director& d = t3::Director::instance();
        const t3::Input& input = d.input();
        if (input.pointing().isTrigger()) {
            //  画面をタッチした
            if (d.getRandomNumberGenerator().getBool()){
                T3_TRACE("A\n");
                t3::EventPtr new_event(new EventAAA);
                t3::safeQueueEvent(new_event);
            }
            else {
                T3_TRACE("B\n");
                t3::EventPtr new_event(new EventBBB);
                t3::safeQueueEvent(new_event);
                
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
    : Scene( "EventHandling" ) {
    context_.reset(T3_NEW SceneContext());
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
        finish(true);
    }
}

void EventHandlingScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















