////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_pause_level.hpp
    ポーズレベル. ex. LV5のポーズ処理はLV4以下の対象も全てポーズさせる
*/

#ifndef TRI_PAUSE_LEVEL_HPP_INCLUDED
#define TRI_PAUSE_LEVEL_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "tri_event.hpp"

TRI_CORE_NS_BEGIN


///
/// ポーズレベル
enum PauseLevel {
    PAUSE_NONE,
    
    PAUSE_LV_1 = 1,
    PAUSE_LV_2,
    PAUSE_LV_3,
    PAUSE_LV_4,
    PAUSE_LV_5,
    PAUSE_LV_6,
    PAUSE_LV_7,
    PAUSE_LV_8
};


TRI_EVENT_NS_BEGIN



///
/// ポーズイベント
class PauseEvent
    : public EventBase {
public:
    ///
    /// コンストラクタ
    PauseEvent(PauseLevel lv)
        : pause_lv_(lv)
    {}

    ///
    /// イベント種別
    static const EventType TYPE;
    
    ///
    /// イベント種別取得
    const EventType& eventType() const override {
        return TYPE;
    }

    ///
    /// ポーズレベル取得
    PauseLevel getPauseLevel() const {
        return pause_lv_;
    }

private:
    PauseLevel pause_lv_;   ///< ポーズレベル
};

///
/// ポーズ解除イベント
class ResumeEvent
    : public EventBase {
public:
    ///
    /// コンストラクタ
    ResumeEvent(PauseLevel lv)
        : pause_lv_(lv)
    {}
    
    ///
    /// イベントタイプ
    static const EventType TYPE;
    
    ///
    /// イベントタイプ取得
    const EventType& eventType() const override {
        return TYPE;
    }

    ///
    /// ポーズレベル取得
    PauseLevel getPauseLevel() const {
        return pause_lv_;
    }
    
private:
    PauseLevel pause_lv_;   ///< ポーズレベル
};


TRI_EVENT_NS_END
TRI_CORE_NS_END



#endif  // TRI_PAUSE_LEVEL_HPP_INCLUDED


