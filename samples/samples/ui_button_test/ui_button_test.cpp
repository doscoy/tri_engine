

#include "ui_button_test.hpp"

namespace {
class EventAAA
    : public t3::EventBase
{
public:
    static const t3::EventType TYPE;
    const t3::EventType& eventType() const override {
        return TYPE;
    }
};
const t3::EventType EventAAA::TYPE("EventAAA123422");


class EventSwapA
    : public t3::EventBase
{
public:
    static const t3::EventType TYPE;
    const t3::EventType& eventType() const override {
        return TYPE;
    }
};
const t3::EventType EventSwapA::TYPE("EventSwapA");

class EventSwapB
    : public t3::EventBase
{
public:
    static const t3::EventType TYPE;
    const t3::EventType& eventType() const override {
        return TYPE;
    }
};
const t3::EventType EventSwapB::TYPE("EventSwapB");


}   //  unname namespace

class UiButtonScene::SceneContext {

public:
    SceneContext()
        : layer_()
        , button_()
        , sprite_(nullptr)
        , swap_button_()
        , swap_a_(nullptr)
        , swap_b_(nullptr)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize() {
        //  通常ボタン
        t3::FilePath path = t3::FilePath("tri_engine_ui_sample.png");
        sprite_ = layer_.createSprite(path);
        sprite_->setupTextureCoordAndSize(t3::Vec2(0, 0), t3::Vec2(64, 64));
        button_.setupSprite(sprite_);
        button_.addTriggeredEvent(
            std::make_shared<EventAAA>()
        );
        button_.size(128);
        
        
        
        //  スワップボタン
        swap_a_ = layer_.createSprite(path);
        swap_a_->setupTextureCoordAndSize(t3::Vec2(0, 128), t3::Vec2(64, 64));
        swap_b_ = layer_.createSprite(path);
        swap_b_->setupTextureCoordAndSize(t3::Vec2(64, 128), t3::Vec2(64, 64));
        
        swap_button_.setupSprite(swap_a_, swap_b_);
        swap_button_.size(128);
        swap_button_.position(t3::Vec2(100, 200));
        
        //  イベント登録
        t3::safeAddListener(this, &SceneContext::onEventAA, EventAAA::TYPE);
        t3::safeAddListener(this, &SceneContext::onSwapA, EventSwapA::TYPE);
        t3::safeAddListener(this, &SceneContext::onSwapB, EventSwapB::TYPE);
        
        
        // ラジオボタン作成
        for (int i = 0; i < RADIO_BUTTON_NUM; ++i) {
            auto spr = layer_.createSprite(path);
            spr->setupTextureCoordAndSize(
                t3::Vec2(0, 64),
                t3::Vec2(64, 64)
            );
            spr->transform()->position(i * 70, -190);
            btn_radio_[i].setupSprite(spr);
            group_.registryButton(&btn_radio_[i]);
        }
        
    }
    
    void terminate() {
        t3::safeRemoveListener(this);
    }
    
    void update(t3::tick_t delta_time) {
        
    }

    void suspend(t3::tick_t delta_time) {

    }
    
    void onEventAA(const t3::Event& eve) {
        T3_TRACE("onEventAA\n");
    }

    void onSwapA(const t3::Event& eve) {
        T3_TRACE("onSwapA\n");
    }
    
    void onSwapB(const t3::Event& eve) {
        T3_TRACE("onSwapB\n");
    }
private:
    t3::SpriteLayer layer_;
    t3::gui::Button button_;
    t3::gfx::SpritePtr sprite_;
    
    t3::SwapButton swap_button_;
    t3::gfx::SpritePtr swap_a_;
    t3::gfx::SpritePtr swap_b_;
    
    
    static const int RADIO_BUTTON_NUM = 3;
    t3::Button btn_radio_[RADIO_BUTTON_NUM];
    t3::RadioButton group_;

    

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
















