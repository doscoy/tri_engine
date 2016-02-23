////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file jet_swap_button.hpp
    スワップボタン.
    ボタンを押す度にA <-> Bと切り替わる
*/

#ifndef JET_SWAP_BUTTON_HPP_INCLUDED
#define JET_SWAP_BUTTON_HPP_INCLUDED

//  include
#include "jet/jet_config.hpp"
#include "jet_button.hpp"

TRI_JET_NS_BEGIN



///
/// スワップボタン.
/// ボタンを押す度にA,Bが切り替わる
class SwapButton
    : Uncopyable {
public:
    ///
    /// コンストラクタ
    SwapButton();

    ///
    /// デストラクタ
    ~SwapButton();
    
public:
    ///
    /// スプライト登録
    void setupSprite(
        SpritePtr a,
        SpritePtr b,
        bool default_a = true
    );
    
    
    ///
    /// イベント
    void triggeredEvent(
        EventPtr event_a,
        EventPtr event_b
    );
    
    ///
    /// ボタンのスプライトのサイズ設定
    void size(float s) {
        a_.size(s);
        b_.size(s);
    }
    
    ///
    /// ボタンのスプライトのサイズ設定
    void size(const Vec2& s) {
        a_.size(s);
        b_.size(s);
    }
    
    ///
    /// 判定エリア設定
    void hitAreaSize(const float s) {
        a_.hitAreaSize(s);
        b_.hitAreaSize(s);
    }

    ///
    /// 判定エリア設定
    void hitAreaSize(const Vec2 s) {
        a_.hitAreaSize(s);
        b_.hitAreaSize(s);
    }
    
    ///
    /// 座標設定
    void position(const Position2D& pos) {
        a_.position(pos);
        b_.position(pos);
    }


private:
    ///
    /// ボタンAが押された時に呼ばれる
    void onTriggeredA(const EventPtr);

    ///
    /// ボタンBが押された時に呼ばれる
    void onTriggeredB(const EventPtr);

private:
    Button a_;  ///< ボタンA
    Button b_;  ///< ボタンB
    UniqueID swap_button_id_;   ///< スワップボタンのID
    EventPtr a_event_;  ///< ボタンAのイベント
    EventPtr b_event_;  ///< ボタンBのイベント
};


TRI_JET_NS_END



#endif  // JET_SWAP_BUTTON_HPP_INCLUDED
