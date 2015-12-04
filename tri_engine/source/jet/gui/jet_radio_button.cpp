////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
#include "jet/gui/jet_radio_button.hpp"

namespace t3 {

//  ラジオボタン押されたイベント
const EventType RadioButtonEvent::TYPE("tri_RadioButtonEvent");



///
///  コンストラクタ
RadioButton::RadioButton()
    : buttons_()
    , group_id_()
    , active_button_idx_(0) {
 
    EventManager::addListener(this, &RadioButton::onRadioButtonTriggered, RadioButtonEvent::TYPE);
}

///
/// デストラクタ
RadioButton::~RadioButton() {
    EventManager::removeListener(this);
}

///
/// ラジオボタンのグループにボタン登録
void RadioButton::registryButton(
    Button* button  ///< 登録するボタン
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


///
/// ラジオボタンが押されたイベントハンドラ
void RadioButton::onRadioButtonTriggered(
    const EventPtr event
) {

    auto radio_event = static_cast<const RadioButtonEvent*>(event.get());
    
    if (radio_event->groupID() != group_id_) {
        //  このラジオボタンで管理されているボタンイベントじゃなかった
        return;
    }
    
    //  このラジオボタンのボタンイベント
    //   インデックス保存
    active_button_idx_ = radio_event->buttonIndex();

    //  管理しているボタンのアクティブ状態変更
    for (auto& button : buttons_) {
    
        if (button->buttonID() == radio_event->buttonID()) {
            button->activate();
        }
        else {
            button->deactivate();
        }
    }
    
}

}   // namespace t3






