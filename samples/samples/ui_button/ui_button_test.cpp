////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


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
        layer_ = t3::SpriteLayer::create();

        //  通常ボタン
        t3::String tex_name = "tri_engine_ui_sample.png";
        sprite_ = layer_->createSprite(tex_name);
        sprite_->setupTextureCoordAndSize(t3::Vec2(0, 0), t3::Vec2(64, 64));
        button_.setupSprite(sprite_);
        button_.addTriggeredEvent(
            std::make_shared<EventAAA>()
        );
        button_.size(128);
        
        
        
        //  スワップボタン
        swap_a_ = layer_->createSprite(tex_name);
        swap_a_->setupTextureCoordAndSize(t3::Vec2(0, 128), t3::Vec2(64, 64));
        swap_b_ = layer_->createSprite(tex_name);
        swap_b_->setupTextureCoordAndSize(t3::Vec2(64, 128), t3::Vec2(64, 64));
        
        swap_button_.setupSprite(swap_a_, swap_b_);
        swap_button_.size(128);
        swap_button_.position(t3::Vec2(100, 200));
        
        //  イベント登録
        t3::EventManager::addListener(this, &SceneContext::onEventAA, EventAAA::TYPE);
        t3::EventManager::addListener(this, &SceneContext::onSwapA, EventSwapA::TYPE);
        t3::EventManager::addListener(this, &SceneContext::onSwapB, EventSwapB::TYPE);
        
        
        // ラジオボタン作成
        for (int i = 0; i < RADIO_BUTTON_NUM; ++i) {
            auto spr = layer_->createSprite(tex_name);
            spr->setupTextureCoordAndSize(
                t3::Vec2(0, 64),
                t3::Vec2(64, 64)
            );
            spr->transform()->position(static_cast<float>(i * 70), -190.0f);
            btn_radio_[i].setupSprite(spr);
            group_.registryButton(&btn_radio_[i]);
        }
        
    }
    
    void terminate() {
        t3::EventManager::removeListener(this);
    }
    
    void update(const t3::FrameInfo& frame_info) {
        
    }
    
    void onEventAA(const t3::EventPtr eve) {
        T3_TRACE_TERMINAL("onEventAA\n");
    }

    void onSwapA(const t3::EventPtr eve) {
        T3_TRACE_TERMINAL("onSwapA\n");
    }
    
    void onSwapB(const t3::EventPtr eve) {
        T3_TRACE_TERMINAL("onSwapB\n");
    }
private:
    t3::SpriteLayerPtr layer_;
    t3::Button button_;
    t3::SpritePtr sprite_;
    
    t3::SwapButton swap_button_;
    t3::SpritePtr swap_a_;
    t3::SpritePtr swap_b_;
    
    
    static const int RADIO_BUTTON_NUM = 3;
    t3::Button btn_radio_[RADIO_BUTTON_NUM];
    t3::RadioButton group_;

    

};






UiButtonScene::UiButtonScene()
    : SceneBase("AudioTest") {
    context_.reset(T3_SYS_NEW SceneContext());
}

UiButtonScene::~UiButtonScene() {
    
}


void UiButtonScene::initializeScene() {
    context_->initialize();
}


void UiButtonScene::terminateScene() {
    context_->terminate();
}


void UiButtonScene::updateScene(const t3::FrameInfo& frame_info) {
    context_->update(frame_info);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

















