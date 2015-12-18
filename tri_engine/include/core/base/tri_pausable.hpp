////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_pausable.hpp
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
    
    PAUSE_LV_1 = 1,
    PAUSE_LV_2,
    PAUSE_LV_3,
    PAUSE_LV_4,
    PAUSE_LV_5,
    PAUSE_LV_6,
    PAUSE_LV_7,
    PAUSE_LV_8,
    
    PAUSE_NONE,
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


///
/// ポーズイベントハンドルクラス
class Pausable {
public:
    Pausable();
    ~Pausable();


public:
    void pauseLevel(PauseLevel lv) {
        pause_lv_ = lv;
    }
    
    PauseLevel pauseLevel() const {
        return pause_lv_;
    }


protected:
    ///
    /// ポーズ
    void pause() {
        pause_ = true;
    }
    
    ///
    /// ポーズ解除
    void resume() {
        pause_ = false;
    }
    
    ///
    /// ポーズ中判定
    bool paused() const {
        return pause_;
    }
    
    
    ///
    /// ポーズイベントハンドラ
    void onPause(const EventPtr e);
    
    ///
    /// レジュームハンドラ
    void onResume(const EventPtr e);

private:
    bool pause_;
    PauseLevel pause_lv_;
};











TRI_CORE_NS_END



#endif  // TRI_PAUSE_LEVEL_HPP_INCLUDED


