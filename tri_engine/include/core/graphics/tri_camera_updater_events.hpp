////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_camera_updater_events.hpp
    カメラ更新イベント.
*/

#ifndef TRI_CAMERA_UPDATER_EVENTS_HPP_INCLUDED
#define TRI_CAMERA_UPDATER_EVENTS_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/base/tri_event.hpp"



TRI_CORE_NS_BEGIN
TRI_EVENT_NS_BEGIN

///
///  カメラ前後ドリー
class CameraDollyFront
    : public EventBase
{
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
    /// 速度設定
    void speed(float s) {
        speed_ = s;
    }
    
    ///
    /// 速度取得
    float speed() const {
        return speed_;
    }

private:
    float speed_;  ///< 移動速度
};

///
///  カメラ水平ドリー
class CameraDollyH
    : public EventBase
{
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
    /// 速度設定
    void speed(float s) {
        speed_ = s;
    }
    
    ///
    /// 速度取得
    float speed() const {
        return speed_;
    }

private:
    float speed_;  ///< 移動速度
};

///
///  カメラ垂直ドリー
class CameraDollyV
    : public EventBase
{
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
    /// 速度設定
    void speed(float s) {
        speed_ = s;
    }
    
    ///
    /// 速度取得
    float speed() const {
        return speed_;
    }

private:
    float speed_;  ///< 移動速度
};

///
///  カメラ垂直パン
class CameraPanV
    : public EventBase
{
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
    /// 速度設定
    void speed(float s) {
        speed_ = s;
    }
    
    ///
    /// 速度取得
    float speed() const {
        return speed_;
    }

private:
    float speed_;  ///< 移動速度
};


///
///  カメラ水平パン
class CameraPanH
    : public EventBase
{
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
    /// 速度設定
    void speed(float s) {
        speed_ = s;
    }
    
    ///
    /// 速度取得
    float speed() const {
        return speed_;
    }

private:
    float speed_;  ///< 移動速度
};

///
///  カメラY軸ロール
class CameraRollH
    : public EventBase
{
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
    /// 速度設定
    void speed(float s) {
        speed_ = s;
    }
    
    ///
    /// 速度取得
    float speed() const {
        return speed_;
    }

private:
    float speed_;  ///< 移動速度
};

///
///  カメラX軸ロール
class CameraRollV
    : public EventBase
{
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
    /// 速度設定
    void speed(float s) {
        speed_ = s;
    }
    
    ///
    /// 速度取得
    float speed() const {
        return speed_;
    }

private:
    float speed_;  ///< 移動速度
};


TRI_EVENT_NS_END
TRI_CORE_NS_END


#endif  // TRI_CAMERA_UPDATER_EVENTS_HPP_INCLUDED

