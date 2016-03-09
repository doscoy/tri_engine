////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_trace.hpp
    デバッグトレース.
*/

#ifndef TRI_TRACE_HPP_INCLUDED
#define TRI_TRACE_HPP_INCLUDED

#include "core/core_config.hpp"
#include "cross/cross_std.hpp"

TRI_CORE_NS_BEGIN

#define T3_TRACE_CHANNEL_MASK_USER          (0x00ff)
#define T3_TRACE_CHANNEL_BIT_USER_0         (1<<0)
#define T3_TRACE_CHANNEL_BIT_USER_1         (1<<1)
#define T3_TRACE_CHANNEL_BIT_USER_2         (1<<2)
#define T3_TRACE_CHANNEL_BIT_USER_3         (1<<3)
#define T3_TRACE_CHANNEL_BIT_USER_4         (1<<4)
#define T3_TRACE_CHANNEL_BIT_USER_5         (1<<5)
#define T3_TRACE_CHANNEL_BIT_USER_6         (1<<6)
#define T3_TRACE_CHANNEL_BIT_USER_7         (1<<7)

#define T3_TRACE_CHANNEL_MASK_SYSTEM        (0xff00)
#define T3_TRACE_CHANNEL_BIT_SYSTEM_LOG     (1<<8)
#define T3_TRACE_CHANNEL_BIT_SYSTEM_WARNING (1<<9)
#define T3_TRACE_CHANNEL_BIT_SYSTEM_DEBUG   (1<<10)

#define T3_TRACE_CHANNEL_MASK_ALL           (T3_TRACE_CHANNEL_MASK_USER|T3_TRACE_CHANNEL_MASK_SYSTEM)


//  前方宣言
class Vec4;

class Mtx44;


///
/// ターミナルにログ出力
void setTraceMask(int mask_bit);

///
/// ターミナルにログ出力
void traceTerminal(const char* const format, ...);

///
/// 画面にログ出力
void traceDisplay(const char* const format, ...);

///
/// ログ出力
void trace(int ch, const char* const format, ...);

///
/// ログ出力
void traceValue(int ch, const char* const name, ::std::size_t value);

///
/// ログ出力.
/// int値
void traceValue(int ch, const char* const name, int value);

///
/// ログ出力.
/// uint32_t版
void traceValue(int ch, const char* const name, uint32_t value);

///
/// ログ出力.
/// long版
void traceValue(int ch, const char* const name, long value);

///
/// ログ出力.
/// uint32_t版
void traceValue(int ch, const char* const name, uint32_t value);

///
/// ログ出力.
/// float版
void traceValue(int ch, const char* const name, float value);

///
/// ログ出力.
/// void*版
void traceValue(int ch, const char* const name, void* value);

///
/// ログ出力.
/// const char*版
void traceValue(int ch, const char* const name, const char* value);

///
/// ログ出力.
/// Vec2版
//void traceValue(int ch, const char* const name, const Vec2& value);

///
/// ログ出力.
/// Vec3版
//void traceValue(int ch, const char* const name, const Vec3& value);

///
/// ログ出力.
/// Vec4版
void traceValue(int ch, const char* const name, const Vec4& value);

///
/// ログ出力.
/// Mtx44版
void traceValue(int ch, const char* const name, const Mtx44& value);



TRI_CORE_NS_END


#ifdef TRI_DEBUG
    #define TRI_DEVELOPMENT_ENABLE_TRACE
#endif // TRI_DEBUG

#ifdef TRI_DEVELOPMENT_ENABLE_TRACE

#define T3_TRACE(ch, ...)           ::t3::trace(ch, __VA_ARGS__)
#define T3_TRACE_PASS()             T3_TRACE(T3_TRACE_CHANNEL_BIT_SYSTEM_DEBUG, "%s[%d]\n", __FUNCTION__, __LINE__);
#define T3_TRACE_VALUE(ch, x)       ::t3::traceValue(ch, #x, x)
#define T3_TRACE_TERMINAL(...)      ::t3::traceTerminal(__VA_ARGS__) // ターミナルのみにトレース。意図が無い場合はT3_TRACEを使う

#define T3_SYSTEM_LOG(...)          T3_TRACE(T3_TRACE_CHANNEL_BIT_SYSTEM_LOG, __VA_ARGS__)
#define T3_SYSTEM_WARNING(...)      T3_TRACE(T3_TRACE_CHANNEL_BIT_SYSTEM_WARNING, __VA_ARGS__)
#define T3_SYSTEM_LOG_DEBUG(...)    T3_TRACE(T3_TRACE_CHANNEL_BIT_SYSTEM_DEBUG, __VA_ARGS__)

#else // TRI_DEVELOPMENT_ENABLE_TRACE

#define T3_TRACE(...)               (void)0
#define T3_TRACE_PASS()             (void)0
#define T3_TRACE_VALUE(x)           (void)0
#define T3_TRACE_TERMINAL(...)      (void)0

#define T3_SYSTEM_LOG(...)          (void)0
#define T3_SYSTEM_WARNING(...)      (void)0
#define T3_SYSTEM_LOG_DEBUG(...)    (void)0

#endif // TRI_DEVELOPMENT_ENABLE_TRACE

#endif // TRI_TRACE_HPP_INCLUDED