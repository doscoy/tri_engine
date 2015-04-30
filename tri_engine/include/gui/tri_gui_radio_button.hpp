

#ifndef TRI_GUI_RADIO_BUTTON_HPP_INCLUDED
#define TRI_GUI_RADIO_BUTTON_HPP_INCLUDED

#include "tri_gui_button.hpp"

namespace t3 {



//  ラジオボタンに登録されているボタンが押された時のイベント
class RadioButtonEvent
    : public EventBase {

    RadioButtonEvent();
public:
    RadioButtonEvent(
        const UniqueID group_id,
        const UniqueID button_id,
        int button_idx
    )   : button_id_(button_id)
        , group_id_(group_id)
        , button_index_(button_idx) {
    }
    
    static const EventType TYPE;
    const EventType& eventType() const override {
        return TYPE;
    }
    
    UniqueID buttonID() const {
        return button_id_;
    }
    
    UniqueID groupID() const {
        return group_id_;
    }
    
    int buttonIndex() const {
        return button_index_;
    }
    
private:
    UniqueID button_id_;
    UniqueID group_id_;
    int button_index_;
};



//  ラジオボタン
class RadioButton {
public:
    RadioButton();
    
    ~RadioButton();
    
public:
    void registryButton(
        Button* button
    );

    int activeButtonIndex() const {
        return active_button_idx_;
    }
    
    UniqueID activeButtonID() const {
        return buttons_[active_button_idx_]->buttonID();
    }

    UniqueID id() {
        return group_id_;
    }

private:
    void onRadioButtonTriggered(
        const Event& event
    );

private:
    Vector<Button*> buttons_;
    UniqueID group_id_;
    int active_button_idx_;
};




}   // t3



#endif  // TRI_GUI_RADIO_BUTTON_HPP_INCLUDED

