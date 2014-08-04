#include "gui/tri_gui_radio_button.hpp"



namespace t3 {
inline namespace gui {

//  ラジオボタン押されたイベント
const EventType RadioButtonEvent::TYPE("RadioButtonEvent");



//  コンストラクタ
RadioButton::RadioButton()
    : buttons_()
    , group_id_()
    , active_button_idx_(0) {
 
    safeAddListener(this, &RadioButton::onRadioButtonTriggered, RadioButtonEvent::TYPE);
}

RadioButton::~RadioButton() {
    safeRemoveListener(this);
}


void RadioButton::registryButton(
    Button* button
) {
    button->addTriggeredEvent(
        std::make_shared<RadioButtonEvent>(
            group_id_,
            button->buttonID(),
            buttons_.size()
        )
    );
    
    buttons_.push_back(button);
}


void RadioButton::onRadioButtonTriggered(
    const Event& event
) {

    auto& radio_event = static_cast<const RadioButtonEvent&>(event);
    
    if (radio_event.groupID() != group_id_) {
        //  このラジオボタンで管理されているボタンイベントじゃなかった
        return;
    }
    
    //  このラジオボタンのボタンイベント
    //   インデックス保存
    active_button_idx_ = radio_event.buttonIndex();

    //  管理しているボタンのアクティブ状態変更
    for (auto& button : buttons_) {
    
        if (button->buttonID() == radio_event.buttonID()) {
            button->activate();
        }
        else {
            button->deactivate();
        }
    }
    
}



}   // namespace gui
}   // namespace t3






