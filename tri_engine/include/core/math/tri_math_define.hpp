/**
    @file tri_define.hpp
    算術系定義.
*/

#ifndef TRI_MATH_DEFINE_INCLUDED
#define TRI_MATH_DEFINE_INCLUDED

#include "core/core_config.hpp"

TRI_CORE_NS_BEGIN

    
constexpr float PI = 3.141592653589793f;    ///< 円周率
constexpr float TWO_PI = PI * 2;            ///< 円周率x2
constexpr float EPSILON = 0.00001f;         ///< 極小値


TRI_CORE_NS_END

#endif // TRI_MATH_DEFINE_INCLUDED