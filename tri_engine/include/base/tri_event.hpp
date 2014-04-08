//
//  tri_event.hpp
//  star
//
//  Created by KANI Tetsuro on 2014/04/08.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#ifndef star_tri_event_hpp
#define star_tri_event_hpp

#include "util/tri_hash_string.hpp"


namespace t3 {
inline namespace base {
    
//  ハッシュ文字列をイベントタイプとして使用
using EventType = HashString;


class EventInterface {
public:
    virtual const EventType& getEventType() const = 0;
    virtual tick_t getTimeStamp() const = 0;
};


class BaseEventData
    : public EventInterface
{
public:
    explicit BaseEventData(
        const float time_stamp = 0.0f
    )   : time_stamp_(time_stamp)
    {
    }
    
    ~BaseEventData() {}
    
public:

    

public:
    tick_t getTimeStamp() const override {
        return time_stamp_;
    }

private:
    const tick_t time_stamp_;
};

}   // namespace base
}   // namespace t3


#endif
