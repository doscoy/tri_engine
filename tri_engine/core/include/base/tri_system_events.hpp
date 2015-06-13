/**
    @file tri_system_events.hpp
    システム定義イベント.
*/

#ifndef TRI_SYSTEM_EVENTS_HPP_INCLUDED
#define TRI_SYSTEM_EVENTS_HPP_INCLUDED

//  include
#include "core_config.hpp"
#include "tri_event.hpp"
#include "math/tri_vec2.hpp"
#include "kernel/io/tri_pointing.hpp"



TRI_CORE_NS_BEGIN



///
///  タッチトリガーイベント
class PointingTriggeredEvent
    : public EventBase {
public:
    ///
    /// イベント種別
    static const EventType TYPE;
    
    ///
    /// イベント種別取得
    const EventType& eventType() const override {
        return TYPE;
    }

    ///
    /// 位置取得
    const Vec2& position() const {
        return pos_;
    }
    
    ///
    /// 位置設定
    void position(const Vec2& pos) {
        pos_ = pos;
    }
    
    ///
    /// 入力番号取得
    int inputNo() const {
        return input_no_;
    }
    
    ///
    /// 入力番号設定
    void inputNo(int no) {
        input_no_ = no;
    }

private:
    Vec2 pos_;      ///< 位置
    int input_no_;  ///< 入力番号
};


///
///  タッチリリースイベント
class PointingReleasedEvent
    : public EventBase {
public:
    ///
    /// イベント種別
    static const EventType TYPE;
    
    ///
    /// イベント種別取得
    const EventType& eventType() const override {
        return TYPE;
    }
    
    ///
    /// 座標取得
    const Vec2& position() const {
        return pos_;
    }
    
    ///
    /// 座標設定
    void position(const Vec2& pos) {
        pos_ = pos;
    }
    
    ///
    /// 入力番号取得
    int inputNo() const {
        return input_no_;
    }
    
    ///
    /// 入力番号設定
    void inputNo(int no) {
        input_no_ = no;
    }

private:
    Vec2 pos_;      ///< 位置
    int input_no_;  ///< 入力番号
};

///
///  タッチムーブイベント
class PointingMovingEvent
    : public EventBase {
public:
    ///
    /// イベント種別
    static const EventType TYPE;
    
    ///
    /// イベント種別取得
    const EventType& eventType() const override {
        return TYPE;
    }
    
    ///
    /// 座標取得
    const Vec2& position() const {
        return pos_;
    }
    
    ///
    /// 座標設定
    void position(const Vec2& pos) {
        pos_ = pos;
    }
    
    ///
    /// 移動量取得
    const Vec2& moveDistance() const {
        return distance_;
    }
    
    ///
    /// 移動量設定
    void moveDistance(const Vec2& distance) {
        distance_ = distance;
    }
    
    ///
    /// 入力番号取得
    int inputNo() const {
        return input_no_;
    }
    
    ///
    /// 入力番号設定
    void inputNo(int no) {
        input_no_ = no;
    }

private:
    Vec2 pos_;      ///< 座標
    Vec2 distance_; ///< 移動距離
    int input_no_;  ///< 入力番号
};


///
///  フリックイベント
class PointingFlickEvent
    : public EventBase {
public:
    ///
    /// イベント種別
    static const EventType TYPE;
    
    ///
    /// イベント種別取得
    const EventType& eventType() const override {
        return TYPE;
    }
    
    ///
    /// 入力番号取得
    int inputNo() const {
        return input_no_;
    }
    
    ///
    /// 入力番号設定
    void inputNo(int no) {
        input_no_ = no;
    }
    
    ///
    /// フリックベクトル取得
    const t3::Vec2& flickMoveOffset() const {
        return dir_;
    }
    
    ///
    /// フリックベクトル設定
    void flickMoveOffset(const t3::Vec2& d) {
        dir_ = d;
    }

    ///
    /// フリック方向取得
    Pointing::FlickDirection flickDirection() const {
        return flick_dir_;
    }
    
    ///
    /// フリック方向設定
    void flickDirection(Pointing::FlickDirection dir) {
        flick_dir_ = dir;
    }

private:
    Vec2 dir_;                              ///< 方向ベクトル
    int input_no_;                          ///< 入力番号
    Pointing::FlickDirection flick_dir_;    ///< フリック方向の種別
};

TRI_CORE_NS_END



#endif  // TRI_SYSTEM_EVENTS_HPP_INCLUDED
