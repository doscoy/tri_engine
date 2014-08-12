
#ifndef TRI_TRACE_HPP_INCLUDED
#define TRI_TRACE_HPP_INCLUDED

#include "base/tri_types.hpp"

namespace t3 {
inline namespace math {

//  前方宣言
template <class T>
struct Vec2Template;

template <class T>
struct Vec3Template;

template <class T>
struct Vec4Template;

template <class T>
struct Mtx44Template;

}   // namespace math


inline namespace dbg {


void traceTerminal(const char* const format, ...);
void traceDisplay(const char* const format, ...);
void trace(const char* const format, ...);

void traceValue(const char* const name, ::std::size_t value);
void traceValue(const char* const name, int value);
void traceValue(const char* const name, uint32_t value);
void traceValue(const char* const name, long value);
void traceValue(const char* const name, uint32_t value);
void traceValue(const char* const name, float value);
void traceValue(const char* const name, void* value);
void traceValue(const char* const name, const char* value);
void traceValue(const char* const name, const Vec2Template<float>& value);
void traceValue(const char* const name, const Vec3Template<float>& value);
void traceValue(const char* const name, const Vec4Template<float>& value);
void traceValue(const char* const name, const Mtx44Template<float>& value);



}   // inline namespace dbg
}   // namespace t3


#ifndef NDEBUG
    #define TRI_DEVELOPMENT_ENABLE_TRACE
#endif // NDEBUG

#ifdef TRI_DEVELOPMENT_ENABLE_TRACE

#define T3_TRACE(...)       ::t3::trace(__VA_ARGS__)
#define T3_TRACE_VALUE(x)   ::t3::traceValue(#x, x)

#else // TRI_DEVELOPMENT_ENABLE_TRACE

#define T3_TRACE(...)       (void)0
#define T3_TRACE_VALUE(x)   (void)0

#endif // TRI_DEVELOPMENT_ENABLE_TRACE

#endif // TRI_TRACE_HPP_INCLUDED