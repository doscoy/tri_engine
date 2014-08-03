
#ifndef TRI_EVENT_HPP_INCLUDED
#define TRI_EVENT_HPP_INCLUDED


#include "util/tri_hash_string.hpp"
#include "base/tri_types.hpp"
#include "util/tri_uncopyable.hpp"
#include <memory>



namespace t3 {
inline namespace base {
    
//  ハッシュ文字列をイベントタイプとして使用
using EventType = HashString;

class Event
    : private Uncopyable
{
public:
    virtual const EventType& eventType() const = 0;
    virtual tick_t timeStamp() const = 0;
};
using EventPtr = std::shared_ptr<Event>;


class EventBase
    : public Event
{
public:
    explicit EventBase(
        const float time_stamp = 0.0f
    )   : time_stamp_(time_stamp)
    {
    }
    
    ~EventBase() {}
    
public:
    virtual const EventType& eventType() const = 0;
    

public:
    tick_t timeStamp() const override {
        return time_stamp_;
    }

private:
    const tick_t time_stamp_;
};

}   // namespace base
}   // namespace t3


#endif  // TRI_EVENT_HPP_INCLUDED
