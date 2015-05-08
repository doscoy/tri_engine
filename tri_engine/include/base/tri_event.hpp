
#ifndef TRI_EVENT_HPP_INCLUDED
#define TRI_EVENT_HPP_INCLUDED

//  include
#include "util/tri_hash_string.hpp"
#include "base/tri_types.hpp"
#include "util/tri_uncopyable.hpp"
#include "tri_std.hpp"


namespace t3 {


using EventType = HashString;   ///< ハッシュ文字列をイベントタイプとして使用

///
/// イベントのインターフェース
class Event
    : private Uncopyable
{
public:
    ///
    /// イベントタイプ
    virtual const EventType& eventType() const = 0;

    ///
    /// タイムスタンプ
    virtual tick_t timeStamp() const = 0;

    ///
    /// イベント名
    String eventName() {
        return eventType().string();
    }
};


using EventPtr = SharedPtr<Event>;  ///< イベントのポインタ


///
/// イベント基底クラス
class EventBase
    : public Event
{
public:
    ///
    /// コンストラクタ
    explicit EventBase(
        const float time_stamp = 0.0f
    )   : time_stamp_(time_stamp)
    {}
    
    ///
    /// デストラクタ
    ~EventBase() {}
    
public:
    ///
    /// イベントタイプ取得
    virtual const EventType& eventType() const = 0;
    

public:
    ///
    /// タイムスタンプ取得
    tick_t timeStamp() const override {
        return time_stamp_;
    }

private:
    ///
    /// タイムスタンプ
    const tick_t time_stamp_;
};


}   // namespace t3


#endif  // TRI_EVENT_HPP_INCLUDED
