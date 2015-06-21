/**
    @file tri_pointing.hpp
    ポインティングデバイス.
*/

#ifndef TRI_POINTING_HPP_INCLUDED
#define TRI_POINTING_HPP_INCLUDED

//  include
#include "cross/cross_sdk.hpp"
#include "../../math/tri_math_types.hpp"
#include "core/base/tri_types.hpp"
#include "core/core_config.hpp"

TRI_CORE_NS_BEGIN


    
///
/// ポインティング入力
class Pointing {
public:
    ///
    /// コンストラクタ
    Pointing();
    
    ///
    /// デストラクタ
    ~Pointing();

    ///
    /// フリックの方向
    enum class FlickDirection {
        UP,     ///< 上
        DOWN,   ///< 下
        RIGHT,  ///< 右
        LEFT    ///< 左
    };

public:
    ///
    /// ポインティングデータの更新
    void updatePointing(
        const cross::PointingData& data,
        tick_t delta_time
    );
    
    ///
    /// ポインティングホールド判定
    bool isHold() const {
        return hold_;
    }
    
    ///
    /// ポインティングトリガ判定
    bool isTrigger() const {
        return trigger_;
    }
    
    ///
    /// ポインティングリリース判定
    bool isRepeat() const {
        return repeat_;
    }
    
    ///
    /// ダブルクリック判定
    bool isDoubleClick() const {
        return double_click_;
    }
    
    ///
    /// ポインティングリリース判定
    bool isRelease() const {
        return release_;
    }
    
    ///
    /// 移動判定
    bool isMoving() const {
        return moved_;
    }

    ///
    /// 座標取得
    const Vec2& position() const {
        return position_[0];
    }

    ///
    /// 移動量取得
    const Vec2& moveDistance() const {
        return moving_;
    }
    
    ///
    /// ポインティングカウント取得
    int getPointingCount() const {
        return pointing_count_;
    }
    
    ///
    /// フリック判定
    bool isFlick() const {
        return flick_;
    }
    
    ///
    /// フリック移動量取得
    const Vec2& flickMoveOffset() const {
    
        return flick_move_;
    }
    
    ///
    /// フリック向き取得
    FlickDirection flickDirection() const {
        return flick_direction_;
    }
    
    

private:
    ///
    /// 座標リストをクリア
    void clearPositionList();
    
    ///
    /// フリックの更新
    void updateFlick();
    
    ///
    /// リピート情報の更新
    void updateRepeat(tick_t delta_time);
    
    ///
    /// スライド情報の更新
    void updateMoving();

private:
    ///
    /// 座標のリストサイズ
    enum {
        MAX_POSITION_SIZE = 60,
    };

    ///
    /// 接触中フラグ
    bool hold_;
    
    ///
    /// 触った瞬間フラグ
    bool trigger_;
    
    ///
    /// 離した瞬間フラグ
    bool release_;
    
    ///
    /// リピートフラグ
    bool repeat_;
    
    ///
    /// 移動フラグ
    bool moved_;
    
    ///
    /// フリックフラグ
    bool flick_;
    
    ///
    /// ダブルクリックフラグ
    bool double_click_;
    
    ///
    /// 座標リスト
    Vec2 position_[MAX_POSITION_SIZE];
    
    ///
    /// 移動量
    Vec2 moving_;
    
    ///
    /// ダブルクリック判定
    float double_click_timer_;
    
    ///
    /// ダブルクリック判定用
    int double_click_release_count_;
    
    ///
    /// リピートのインターバル
    float repeat_interval_;
    
    ///
    /// 押してる時間
    float pressed_time_;
    
    ///
    /// 管理座標数
    int pointing_count_;
    
    ///
    /// 触った瞬間座標
    Vec2 trigged_position_;
    
    ///
    /// 離した瞬間座標
    Vec2 released_position_;
    
    ///
    /// フリック移動量
    Vec2 flick_move_;
    
    ///
    /// フリック方向
    FlickDirection flick_direction_;
};


TRI_CORE_NS_END

#endif // TRI_POINTING_HPP_INCLUDED

