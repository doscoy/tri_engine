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

#include "../core_config.hpp"
#include "tri_math_define.hpp"


TRI_CORE_NS_BEGIN





///
/// ラジアン角
class Radian {
    float angle_;
public:
    Radian()
        : angle_(0)
    {}

    Radian(float angle)
        : angle_(angle)
    {}
    
    float value() const {
        return angle_;
    }

	Radian operator +(Radian rhs) const {
		return angle_ + rhs.angle_;
	}

	Radian operator -(Radian rhs) const {
		return angle_ - rhs.angle_;
	}

	Radian operator *(Radian rhs) const {
		return angle_ * rhs.angle_;
	}

	Radian operator /(Radian rhs) const {
		return angle_ / rhs.angle_;
	}

	Radian operator +() const {
		return *this;
	}

	Radian operator -() const {
		return Radian(-angle_);
	}

	void operator +=(Radian rhs) {
		angle_ += rhs.angle_;
	}

	void operator -=(Radian rhs) {
		angle_ -= rhs.angle_;
	}

	void operator *=(Radian rhs) {
		angle_ *= rhs.angle_;
	}

	void operator /=(Radian rhs) {
		angle_ /= rhs.angle_;
	}
};

///
/// デグリー角
class Degree {
    float angle_;
public:
    Degree()
        : angle_(0)
    {}

    Degree(float angle)
        : angle_(angle)
    {}
    
    float value() const {
        return angle_;
    }

	Degree operator +(Degree rhs) const {
		return angle_ + rhs.angle_;
	}

	Degree operator -(Degree rhs) const {
		return angle_ - rhs.angle_;
	}

	Degree operator *(Degree rhs) const {
		return angle_ * rhs.angle_;
	}

	Degree operator /(Degree rhs) const {
		return angle_ / rhs.angle_;
	}

	Degree operator +() const {
		return *this;
	}

	Degree operator -() const {
		return Degree(-angle_);
	}

	void operator +=(Degree rhs) {
		angle_ += rhs.angle_;
	}

	void operator -=(Degree rhs) {
		angle_ -= rhs.angle_;
	}

	void operator *=(Degree rhs) {
		angle_ *= rhs.angle_;
	}

	void operator /=(Degree rhs) {
		angle_ /= rhs.angle_;
	}
};



///
/// デグリーからラジアンへ変換
inline Radian toRadian(const Degree& degree) {
    return Radian(degree.value() * PI / 180.0f);
}




///
/// ラジアンからデグリーへ変換
inline Degree toDegree(const Radian& radian) {
    return Degree(radian.value() / PI * 180.0f);
}


TRI_CORE_NS_END

#endif // TRI_ANGLE_TYPES_HPP_INCLUDED
