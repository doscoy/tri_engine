//
//  tri_gui_swap_button.cpp
//  tri_samples_ios
//
//  Created by KANI Tetsuro on 2014/07/20.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#include "gui/tri_gui_swap_button.hpp"

namespace t3 {

namespace {


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

const EventType SwapButtonAEvent::TYPE("SwapButtonAEvent");
const EventType SwapButtonBEvent::TYPE("SwapButtonBEvent");


}   // unname namespace


inline namespace gui {

SwapButton::SwapButton()
    : a_()
    , b_()
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
    a_.sprite()->enable(default_a);
    b_.sprite()->enable(!default_a);

    //  イベント登録
    a_.triggerdEvent(std::make_shared<SwapButtonAEvent>(button_id_));
    b_.triggerdEvent(std::make_shared<SwapButtonBEvent>(button_id_));


}

void SwapButton::triggeredEvent(
    EventPtr event_a,
    EventPtr event_b
) {
    a_event_ = event_a;
    b_event_ = event_b;
}


void SwapButton::onTriggeredA(const t3::Event& eve) {
    auto event = static_cast<const SwapButtonAEvent&>(eve);
    if (event.ui_id_ != button_id_) {
        //  自分のボタンイベントじゃない
        return;
    }
    
    
    if (a_event_) {
        safeQueueEvent(a_event_);
    }
    a_.sprite()->enable(false);
    b_.sprite()->enable(true);
}

void SwapButton::onTriggeredB(const t3::Event& eve) {
    auto event = static_cast<const SwapButtonBEvent&>(eve);
    if (event.ui_id_ != button_id_) {
        //  自分のボタンイベントじゃない
        return;
    }

    if (b_event_) {
        safeQueueEvent(b_event_);
    }
    a_.sprite()->enable(true);
    b_.sprite()->enable(false);
}


}   // gui
}   // t3




