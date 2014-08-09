
#include "gui/tri_gui_swap_button.hpp"

namespace t3 {

namespace {

//  スワップボタンのAが押された時のイベント
class SwapButtonAEvent
    : public EventBase {

    SwapButtonAEvent();
public:
    SwapButtonAEvent(UniqueID id)
        : ui_id_(id)
    {}
    
    static const EventType TYPE;
    const EventType& eventType() const override {
        return TYPE;
    }
    UniqueID ui_id_;
};
const EventType SwapButtonAEvent::TYPE("SwapButtonAEvent");


//  スワップボタンのBが押された時のイベント
class SwapButtonBEvent
    : public EventBase {
    SwapButtonBEvent();
public:
    SwapButtonBEvent(UniqueID id)
        : ui_id_(id)
    {}
    static const EventType TYPE;
    const EventType& eventType() const override {
        return TYPE;
    }
    UniqueID ui_id_;
};
const EventType SwapButtonBEvent::TYPE("SwapButtonBEvent");


}   // unname namespace


inline namespace gui {

SwapButton::SwapButton()
    : a_()
    , b_()
    , swap_button_id_()
    , a_event_(nullptr)
    , b_event_(nullptr)
{
    safeAddListener(this, &SwapButton::onTriggeredA, SwapButtonAEvent::TYPE);
    safeAddListener(this, &SwapButton::onTriggeredB, SwapButtonBEvent::TYPE);
}

SwapButton::~SwapButton()
{
    safeRemoveListener(this);
}

void SwapButton::setupSprite(
    SpritePtr a,
    SpritePtr b,
    bool default_a
) {
    //  使用するスプライトを設定
    a_.setupSprite(a);
    b_.setupSprite(b);

    //  初期状態ではAのスプライトだけ表示
    if (default_a) {
        a_.sprite()->enable();
        b_.sprite()->disable();
    } else {
        a_.sprite()->disable();
        b_.sprite()->enable();
    }

    //  イベント登録
    a_.addTriggeredEvent(std::make_shared<SwapButtonAEvent>(swap_button_id_));
    b_.addTriggeredEvent(std::make_shared<SwapButtonBEvent>(swap_button_id_));


}

void SwapButton::triggeredEvent(
    EventPtr event_a,
    EventPtr event_b
) {
    a_event_ = event_a;
    b_event_ = event_b;
}


void SwapButton::onTriggeredA(const t3::Event& eve) {
    auto& event = static_cast<const SwapButtonAEvent&>(eve);
    if (event.ui_id_ != swap_button_id_) {
        //  自分のボタンイベントじゃない
        return;
    }
    
    
    if (a_event_) {
        safeQueueEvent(a_event_);
    }
    a_.sprite()->disable();
    b_.sprite()->enable();
}

void SwapButton::onTriggeredB(const t3::Event& eve) {
    auto& event = static_cast<const SwapButtonBEvent&>(eve);
    if (event.ui_id_ != swap_button_id_) {
        //  自分のボタンイベントじゃない
        return;
    }

    if (b_event_) {
        safeQueueEvent(b_event_);
    }
    a_.sprite()->enable();
    b_.sprite()->disable();
}


}   // gui
}   // t3




