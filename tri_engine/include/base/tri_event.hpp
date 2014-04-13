
#ifndef TRI_EVENT_HPP_INCLUDED
#define TRI_EVENT_HPP_INCLUDED


#include "util/tri_hash_string.hpp"
#include "base/tri_types.hpp"
#include <memory>



namespace t3 {
inline namespace base {
    
//  ハッシュ文字列をイベントタイプとして使用
using EventType = HashString;


class EventInterface {
public:
    virtual const EventType& getEventType() const = 0;
    virtual tick_t getTimeStamp() const = 0;
};

using EventInterfacePtr = std::shared_ptr<EventInterface>;

class Event
    : public EventInterface
{
public:
    explicit Event(
        const float time_stamp = 0.0f
    )   : time_stamp_(time_stamp)
    {
    }
    
    ~Event() {}
    
public:
    virtual const EventType& getEventType() const = 0;
    

public:
    tick_t getTimeStamp() const override {
        return time_stamp_;
    }

private:
    const tick_t time_stamp_;
};

}   // namespace base
}   // namespace t3


#endif  // TRI_EVENT_HPP_INCLUDED
