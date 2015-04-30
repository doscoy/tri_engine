
#ifndef TRI_TRACE_HPP_INCLUDED
#define TRI_TRACE_HPP_INCLUDED

#include "base/tri_std.hpp"

namespace t3 {


//  前方宣言
template <class T>
struct Vec2Template;

template <class T>
struct Vec3Template;

template <class T>
struct Vec4Template;

template <class T>
struct Mtx44Template;





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




}   // namespace t3


#ifdef DEBUG
    #define TRI_DEVELOPMENT_ENABLE_TRACE
#endif // DEBUG

#ifdef TRI_DEVELOPMENT_ENABLE_TRACE

#define T3_TRACE(...)           ::t3::trace(__VA_ARGS__)
#define T3_TRACE_PASS()         T3_TRACE("%s[%d]\n", __FUNCTION__, __LINE__);
#define T3_TRACE_VALUE(x)       ::t3::traceValue(#x, x)
#define T3_TRACE_TERMINAL(...)  ::t3::traceTerminal(__VA_ARGS__) // ターミナルのみにトレース。意図が無い場合はT3_TRACEを使う

#else // TRI_DEVELOPMENT_ENABLE_TRACE

#define T3_TRACE(...)           (void)0
#define T3_TRACE_PASS()         (void)0
#define T3_TRACE_VALUE(x)       (void)0
#define T3_TRACE_TERMINAL(...)  (void)0

#endif // TRI_DEVELOPMENT_ENABLE_TRACE

#endif // TRI_TRACE_HPP_INCLUDED