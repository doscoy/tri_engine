////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_interpolation.hpp
    補間処理.
*/

#ifndef TRI_INTERPOLATION_HPP_INCLUDED
#define TRI_INTERPOLATION_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "../base/tri_types.hpp"

TRI_CORE_NS_BEGIN


///
/// 補間タイプ
enum class InterpolationType{
    LINER,            /// 線形補間
    ACCELERATION,     /// 加速補間
    DECELERATION,     ///< 減速補間
};





///
///  線形補間関数
template <typename T>
inline void interpolateLiner(
    T& dest,            ///< 結果
    const T& x0,        ///< 開始値
    const T& x1,        ///< 終了値
    const float t       ///< 割合 t
) {
    dest = x0 + (( x1 - x0 ) * t);
}

/// 
///  曲線補間関数
template <typename T>
inline void interpolateT2(
    T& dest,            ///< 結果
    const T& x0,        ///< 開始値
    const T& x1,        ///< 終了値
    const float t       ///< 割合 t
) {
    float t2 = t * t;
    interpolateLiner( dest, x0, x1, t2 );
}





///
///  補間
template <typename T>
class Interpolation {
private:
    ///
    /// 補間にかかる時間
    float interpolation_time_;

    ///
    /// 補間開始からの経過時間
    float now_time_;

    ///
    /// 有効フラグ
    bool active_;

    ///
    /// 補間タイプ
    InterpolationType type_;

    ///
    /// 補間開始値
    T start_;

    ///
    /// 補間終了値
    T goal_;

    ///
    /// 補間結果適用変数
    T* target_;

public:
    ///
    ///  コンストラクタ
    Interpolation()
        : interpolation_time_( 0.0f )
        , now_time_( 0.0f )
        , active_( false )
        , type_(InterpolationType::LINER)
    {}

    ///
    ///  デストラクタ
    ~Interpolation()
    {}

public:
    ///
    ///  補間開始
    void startInterpolation(
        T& target,                      ///< 操作対象変数
        const T& goal,                  ///< 終了値
        const float time,               ///< 遷移時間
        const InterpolationType type    ///< 補間タイプ
    ){
        //  タイマー初期化
        interpolation_time_ = time;
        now_time_ = 0.0f;

        //  補間タイプ保持
        type_ = type;
    
        //  補間値更新
        target_ = &target;
        start_ = target;
        goal_ = goal;

        //  アクティベート
        active_ = true;
    }

    ///
    ///  更新処理
    void updateInterpolation(const tick_t delta_time) {
        if (!active_) {
            //  startされていないのですぐ終了
            return;
        }

        //  時間更新
        now_time_ += delta_time;

        float t = 0;
        if (interpolation_time_ < now_time_) {
            t = 1.0f;
            active_ = false;
        } else {
            t = now_time_ / interpolation_time_;
        }
        
        //  補間処理
        switch ( type_ ){
            //  線形
            case InterpolationType::LINER:
                interpolateLiner(*target_, start_, goal_, t);
                break;

            //  後半加速
            case InterpolationType::ACCELERATION:
                interpolateT2(*target_, start_, goal_, t);
                break;
                
            //  後半減速
            case InterpolationType::DECELERATION:
                interpolateLiner(*target_, start_, goal_, t);
                break;

        }
    }

    ///
    ///  有効判定
    bool isActive() const { 
        return active_;
    }
};


TRI_CORE_NS_END

#endif // TRI_INTERPOLATION_HPP_INCLUDED


