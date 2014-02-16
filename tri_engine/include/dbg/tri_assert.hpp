
#ifndef TRI_ASSERT_HPP_INCLUDED
#define TRI_ASSERT_HPP_INCLUDED

#include <cmath>

namespace t3 {

bool panic( 
    const char* const exp,
    const char* const filename,
    const int line,
    const char* const funcname,
    const char* const fmt,
    ... 
);

bool isInvalidFloat(const float f);

} // namespace t3

#define ENABLE_ASSERT

#ifdef ENABLE_ASSERT

#define T3_PANIC(...)           t3::panic( "panic", __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__ )
#define T3_ASSERT(exp)          (void)( (exp) || (t3::panic( #exp, __FILE__, __LINE__, __FUNCTION__, "assert" )),0)
#define T3_ASSERT_MSG(exp,...)  (void)( (exp) || (t3::panic( #exp, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__ )),0)
#define T3_NULL_ASSERT(p)       T3_ASSERT_MSG( p != nullptr, "pointer must not be null." )
#define T3_FLOAT_ASSERT(f)      T3_ASSERT_MSG( t3::isInvalidFloat(f), "invalid float." )


#else // ENABLE_ASSERT


#define T3_PANIC(...)           (void)0
#define T3_ASSERT(exp)          (void)0
#define T3_ASSERT_MSG(exp)      (void)0
#define T3_NULL_ASSERT(p)       (void)0
#define T3_FLOAT_ASSERT(f)      (void)0

#endif // ENABLE_ASSERT



#endif // TRI_ASSERT_HPP_INCLUDED