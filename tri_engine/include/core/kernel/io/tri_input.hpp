////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_input.hpp
    入力情報.
*/

#ifndef TRI_INPUT_HPP_INCLUDED
#define TRI_INPUT_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "tri_pad.hpp"
#include "tri_pointing.hpp"


TRI_CORE_NS_BEGIN


///
/// 入力情報
class Input
    : private Uncopyable
{
public:
    ///
    /// パッド情報取得
    const Pad& pad() const {
        return pad_;
    }
    
    ///
    /// ポインティング情報取得
    const Pointing& pointing() const {
        return pointing_;
    }
    
    ///
    /// 加速度センサー情報取得
    const cross::AccelerometerData& accelerometer() const {
        return accele_;
    }


    ///
    /// ゲームパッド情報を更新
    void updatePad(
        const cross::GamePadData& paddata,
        DeltaTime delta_time
    ) {
        pad_.updatePad(paddata, delta_time);
    }
    
    ///
    /// ポインティングデバイス情報を更新
    void updatePointing(
        const cross::PointingData& pointing_data,
        DeltaTime delta_time
    ) {
        pointing_.updatePointing(pointing_data, delta_time);
    }
    
    ///
    /// 加速度センサー情報を更新
    void updateAccelermeter(
        const cross::AccelerometerData acc_data,
        DeltaTime delta_time
    ) {
        (void)delta_time;
        accele_ = acc_data;
    }

    
private:
    Pad pad_;                           ///< ゲームパッド情報
    Pointing pointing_;                 ///< ポインティングデバイス情報
    cross::AccelerometerData accele_;   ///< 加速度センサー
};
  

TRI_CORE_NS_END


#endif // TRI_PAD_HPP_INCLUDED

