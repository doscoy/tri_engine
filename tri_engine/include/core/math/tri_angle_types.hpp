////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_math_types.hpp
    算術系型定義.
*/

#ifndef TRI_ANGLE_TYPES_HPP_INCLUDED
#define TRI_ANGLE_TYPES_HPP_INCLUDED

#include "core_config.hpp"
#include "tri_math_define.hpp"


TRI_CORE_NS_BEGIN





///
/// ラジアン角
class Degree;
class Radian {
    float angle_;
public:
    Radian(float angle);
    
    float angle() const {
        return angle_;
    }
};

///
/// デグリー角
class Degree {
    float angle_;
public:
    Degree(float angle);
    
    float angle() const {
        return angle_;
    }
};



///
/// デグリーからラジアンへ変換
inline Radian toRadian(Degree& degree) {
    return Radian(degree.angle() * PI / 180.0f);
}




///
/// ラジアンからデグリーへ変換
inline Degree toDegree(Radian& radian) {
    return Degree(radian.angle() / PI * 180.0f);
}


TRI_CORE_NS_END

#endif // TRI_ANGLE_TYPES_HPP_INCLUDED
