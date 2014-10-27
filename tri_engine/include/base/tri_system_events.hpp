//
//  tri_system_events.hpp
//  tri_samples_ios
//
//  Created by KANI Tetsuro on 2014/07/20.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#ifndef TRI_SYSTEM_EVENTS_HPP_INCLUDED
#define TRI_SYSTEM_EVENTS_HPP_INCLUDED

#include "tri_event.hpp"
#include "math/tri_vec2.hpp"
#include "kernel/io/tri_pointing.hpp"



namespace t3 {
inline namespace events {


//  タッチトリガーイベント
class PointingTriggeredEvent
    : public EventBase {
public:
    static const EventType TYPE;
    const EventType& eventType() const override {
        return TYPE;
    }

    const Vec2& position() const {
        return pos_;
    }
    
    void position(const Vec2& pos) {
        pos_ = pos;
    }
    
    int inputNo() const {
        return input_no_;
    }
    
    void inputNo(int no) {
        input_no_ = no;
    }

private:
    Vec2 pos_;
    int input_no_;
};

//  タッチリリースイベント
class PointingReleasedEvent
    : public EventBase {
public:
    static const EventType TYPE;
    const EventType& eventType() const override {
        return TYPE;
    }
    const Vec2& position() const {
        return pos_;
    }
    
    void position(const Vec2& pos) {
        pos_ = pos;
    }
    
    int inputNo() const {
        return input_no_;
    }
    
    void inputNo(int no) {
        input_no_ = no;
    }

private:
    Vec2 pos_;
    int input_no_;
};

//  タッチムーブイベント
class PointingMovingEvent
    : public EventBase {
public:
    static const EventType TYPE;
    const EventType& eventType() const override {
        return TYPE;
    }
    const Vec2& position() const {
        return pos_;
    }
    
    void position(const Vec2& pos) {
        pos_ = pos;
    }
    
    const Vec2& moveDistance() const {
        return distance_;
    }
    
    void moveDistance(const Vec2& distance) {
        distance_ = distance;
    }
    
    int inputNo() const {
        return input_no_;
    }
    
    void inputNo(int no) {
        input_no_ = no;
    }

private:
    Vec2 pos_;
    Vec2 distance_;
    int input_no_;
};


//  フリックイベント
class PointingFlickEvent
    : public EventBase {
public:
    static const EventType TYPE;
    const EventType& eventType() const override {
        return TYPE;
    }
    
    int inputNo() const {
        return input_no_;
    }
    
    void inputNo(int no) {
        input_no_ = no;
    }
    
    const t3::Vec2& flickMoveOffset() const {
        return dir_;
    }
    
    void flickMoveOffset(const t3::Vec2& d) {
        dir_ = d;
    }

    Pointing::FlickDirection flickDirection() const {
        return flick_dir_;
    }
    
    void flickDirection(Pointing::FlickDirection dir) {
        flick_dir_ = dir;
    }

private:
    Vec2 dir_;
    int input_no_;
    Pointing::FlickDirection flick_dir_;
};





}   //  namespace events
}   //  namespace t3



#endif  // TRI_SYSTEM_EVENTS_HPP_INCLUDED
