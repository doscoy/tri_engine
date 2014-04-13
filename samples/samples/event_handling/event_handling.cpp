

#include "event_handling.hpp"



class EventAAA
    : public t3::Event
{
public:
    static const t3::EventType ev_;
    const t3::EventType& getEventType() const {
        return ev_;
    }
    
    explicit EventAAA()
        : hp_(300)
    {
        T3_TRACE("aaa ctr.\n");
    }
    
    ~EventAAA() {
        T3_TRACE("aaa dtr\n");
    }

    int hp_;
};


class EventBBB
    : public t3::Event
{
public:
    static const t3::EventType ev_;
    const t3::EventType& getEventType() const {
        return ev_;
    }
    
    explicit EventBBB()
    : hp_(234)
    {
        T3_TRACE("bbb ctr.\n");
    }
    
    ~EventBBB() {
        T3_TRACE("bbb dtr\n");
    }
    
    int hp_;
};

const t3::EventType EventAAA::ev_("aaa");
const t3::EventType EventBBB::ev_("bbb");



class HpText
    : public t3::EventListener
{
public:
    HpText(){
        T3_TRACE("HpText ctr\n");
    }
    ~HpText(){
        T3_TRACE("HpText dtr\n");
    }
    
public:
    const char* getListenerName() const override {
        return "HpText";
    }
    
    bool handleEvent(const t3::EventInterface& event) override {
    
        const EventAAA& aaa = static_cast<const EventAAA&>(event);
    
        T3_TRACE("aaa hp %d\n", aaa.hp_);
    
        return false;
    }
};


class EventHandlingScene::SceneContext {

public:
    SceneContext()
        : snoop_(new t3::EventSnooper())
        , hp_text_(new HpText)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize(){
        t3::safeAddListener(snoop_, t3::EventType("aaa"));
        t3::safeAddListener(hp_text_, t3::EventType("aaa"));
        t3::safeAddListener(hp_text_, t3::EventType("bbb"));
    }
    
    void terminate(){
        t3::safeRemoveListener(snoop_, t3::EventType("aaa"));
        t3::safeRemoveListener(hp_text_, t3::EventType("aaa"));
    }
    
    void update(t3::tick_t delta_time){
        t3::GameSystem& game_system = t3::GameSystem::getInstance();
        const t3::Input& input = game_system.getInput();
        if (input.getPointing().isTrigger()) {
            //  画面をタッチした
            if (game_system.getRandomNumberGenerator().getBool()){
            
                t3::EventInterfacePtr new_event(new EventAAA);
                t3::safeQueEvent(new_event);
            }
            else {
                t3::EventInterfacePtr new_event(new EventBBB);
                t3::safeQueEvent(new_event);
                
            }
        }
    }

    void suspend(t3::tick_t delta_time) {
    
    }

    
private:


private:
    t3::EventListenerPtr snoop_;
    t3::EventListenerPtr hp_text_;
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
    
    t3::GameSystem& gs = t3::GameSystem::getInstance();
    const t3::Pad& pad = gs.getInput().getPad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish_ = true;
    }
}

void EventHandlingScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}















