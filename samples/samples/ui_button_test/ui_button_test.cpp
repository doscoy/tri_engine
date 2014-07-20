

#include "ui_button_test.hpp"

namespace {
class EventAAA
    : public t3::EventBase
{
public:
    EventAAA(){}
    ~EventAAA(){}
    static const t3::EventType TYPE;
    const t3::EventType& eventType() const override {
        return TYPE;
    }
};

const t3::EventType EventAAA::TYPE("EventAAA123422");
}


class UiButtonScene::SceneContext {

public:
    SceneContext()
        : layer_()
        , button_()
        , sprite_(nullptr)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize() {
        t3::FilePath path = t3::FilePath("stamp.png");
        sprite_ = layer_.createSprite(path);
        sprite_->size(128.0f);
        sprite_->adjustPivotByCenter();
        button_.setupSprite(sprite_);
        button_.triggerdEvent(
            std::make_shared<EventAAA>()
        );
        
        t3::safeAddListener(this, &SceneContext::onEventAA, EventAAA::TYPE);
    }
    
    void terminate() {

    }
    
    void update(t3::tick_t delta_time) {
        
    }

    void suspend(t3::tick_t delta_time) {

    }
    
    void onEventAA(const t3::Event& eve) {
        T3_TRACE("onEventAA\n");
    }

    
private:
    t3::SpriteLayer layer_;
    t3::gui::Button button_;
    t3::gfx::SpritePtr sprite_;
};






UiButtonScene::UiButtonScene()
    : Scene( "AudioTest" ) {
    context_.reset(T3_NEW SceneContext());
}

UiButtonScene::~UiButtonScene() {
    
}


void UiButtonScene::initializeScene() {
    context_->initialize();
}


void UiButtonScene::terminateScene() {
    context_->terminate();
}


void UiButtonScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish(true);
    }
}

void UiButtonScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















