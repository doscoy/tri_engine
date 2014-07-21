//
//  tri_gui_swap_button.hpp
//  tri_samples_ios
//
//  Created by KANI Tetsuro on 2014/07/20.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#ifndef TRI_GUI_SWAP_BUTTON_HPP_INCLUDED
#define TRI_GUI_SWAP_BUTTON_HPP_INCLUDED

#include "tri_gui_button.hpp"

namespace t3 {
inline namespace gui {



class SwapButton
    : Uncopyable {
public:
    SwapButton();
    ~SwapButton();
    
public:
    void setupSprite(
        SpritePtr a,
        SpritePtr b,
        bool default_a = true
    );
    
    
    void triggeredEvent(
        EventPtr event_a,
        EventPtr event_b
    );
    
    void size(float s) {
        a_.size(s);
        b_.size(s);
    }
    
    void size(const Vec2& s) {
        a_.size(s);
        b_.size(s);
    }
    
    void hitAreaSize(const float s) {
        a_.hitAreaSize(s);
        b_.hitAreaSize(s);
    }

    void hitAreaSize(const Vec2 s) {
        a_.hitAreaSize(s);
        b_.hitAreaSize(s);
    }
    
    void position(const Vec2& pos) {
        a_.position(pos);
        b_.position(pos);
    }


private:
    void onTriggeredA(const Event&);
    void onTriggeredB(const Event&);

private:
    Button a_;
    Button b_;
    UniqueID button_id_;
    EventPtr a_event_;
    EventPtr b_event_;
};

}   // namespace gui
}   // namespace t3



#endif  // TRI_GUI_SWAP_BUTTON_HPP_INCLUDED
