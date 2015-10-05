////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_event.hpp
    イベント基底.
*/

#ifndef TRI_EVENT_HPP_INCLUDED
#define TRI_EVENT_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/utility/tri_hash_string.hpp"
#include "core/base/tri_types.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "tri_std.hpp"


TRI_CORE_NS_BEGIN


using EventType = HashString;   ///< ハッシュ文字列をイベントタイプとして使用

///
/// イベント基底クラス
class EventBase
    : public Uncopyable
{
public:
    ///
    /// コンストラクタ
    EventBase()
       : delay_(0.0f)
    {}
    
    ///
    /// デストラクタ
    virtual ~EventBase() {}
    
public:
    ///
    /// イベントタイプ取得
    virtual const EventType& eventType() const = 0;
    

public:
    ///
    /// イベント発行までの時間取得
    tick_t delay() const {
        return delay_;
    }
    
    ///
    /// イベント発行までの時間設定
    void delay(tick_t delay) {
        delay_ = delay;
    }
    
    ///
    /// イベント発行までの時間経過
    void update(tick_t dt) {
        delay_ -= dt;
    }

    ///
    /// イベント発行可能か判定
    bool isReady() const {
        return delay_ <= 0.0f;
    }

    ///
    /// イベント名
    String eventName() {
        return eventType().string();
    }

private:
    ///
    /// イベント発行までの時間
    tick_t delay_;
};

using EventPtr = SharedPtr<EventBase>;  ///< イベントのポインタ


TRI_CORE_NS_END


#endif  // TRI_EVENT_HPP_INCLUDED
