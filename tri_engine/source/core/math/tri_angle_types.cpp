////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
 *
 * 角度
 *
 **/


#include "core/math/tri_angle_types.hpp"


TRI_CORE_NS_BEGIN






TRI_CORE_NS_END



//  vec2.cppの代わりに間借り
#include "core/math/tri_vec2.hpp"

TRI_CORE_NS_BEGIN

Vec2& Vec2::operator *=(const Scale2D& rhs) {
    x_ *= rhs.x_;
    y_ *= rhs.y_;
    return *this;
}



TRI_CORE_NS_END


