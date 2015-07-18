
#include "jet/gui/jet_swap_button.hpp"

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



SwapButton::SwapButton()
    : a_()
    , b_()
    , swap_button_id_()
    , a_event_(nullptr)
    , b_event_(nullptr)
{
    EventManager::addListener<SwapButton>(this, &SwapButton::onTriggeredA, SwapButtonAEvent::TYPE);
    EventManager::addListener<SwapButton>(this, &SwapButton::onTriggeredB, SwapButtonBEvent::TYPE);
}

SwapButton::~SwapButton()
{
    EventManager::removeListener(this);
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
        a_.sprite()->show();
        b_.sprite()->hide();
    } else {
        a_.sprite()->hide();
        b_.sprite()->show();
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


void SwapButton::onTriggeredA(const t3::EventPtr eve) {
    auto event = static_cast<const SwapButtonAEvent*>(eve.get());
    if (event->ui_id_ != swap_button_id_) {
        //  自分のボタンイベントじゃない
        return;
    }
    
    
    if (a_event_) {
        EventManager::queueEvent(a_event_);
    }
    a_.sprite()->hide();
    b_.sprite()->show();
}

void SwapButton::onTriggeredB(const t3::EventPtr eve) {
    auto event = static_cast<const SwapButtonBEvent*>(eve.get());
    if (event->ui_id_ != swap_button_id_) {
        //  自分のボタンイベントじゃない
        return;
    }

    if (b_event_) {
        EventManager::queueEvent(b_event_);
    }
    a_.sprite()->show();
    b_.sprite()->hide();
}


}   // t3




