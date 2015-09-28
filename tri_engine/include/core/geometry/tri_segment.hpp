////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_segment.hpp
    線分プリミティブ.
*/

#ifndef TRI_SEGMENT_HPP_INCLUDED
#define TRI_SEGMENT_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "../math/tri_vec3.hpp"

TRI_CORE_NS_BEGIN


///
/// 線分プリミティブ
class Segment {
public:
    
    ///
    /// コンストラクタ
    Segment()
        : a_(0, 0, 1)
        , b_(0, 0, 0)
    {}
    
    ///
    /// コンストラクタ
    Segment(
        const Vec3& a,
        const Vec3& b
    )   : a_(a)
        , b_(b)
    {}
    

    ///
    /// デストラクタ
    ~Segment() = default;
    
    ///
    /// 始点を設定
    const Vec3* getPointA() const {
        return &a_;
    }
    
    ///
    /// 終点を設定
    const Vec3* getPointB() const {
        return &b_;
    }

private:
    ///
    /// 始点
    Vec3 a_;
    
    ///
    /// 終点
    Vec3 b_;
};



TRI_CORE_NS_END


#endif // TRI_SEGMENT_HPP_INCLUDED

