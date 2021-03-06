////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_assert.hpp
    デバッグアサート.
*/

#ifndef TRI_ASSERT_HPP_INCLUDED
#define TRI_ASSERT_HPP_INCLUDED

#include "core/core_config.hpp"
#include "cross/cross_render_system.hpp"

TRI_CORE_NS_BEGIN

///
/// 強制停止
bool panic(
    const char* const exp,
    const char* const filename,
    const int line,
    const char* const funcname,
    const char* const fmt,
    ... 
);

///
/// floatが正常か判定
bool isInvalidFloat(const float f);


TRI_CORE_NS_END




#ifdef DEBUG
    #define ENABLE_ASSERT   1
#else
    #define ENABLE_ASSERT   0
#endif // DEBUG

#if ENABLE_ASSERT

/*! @brief パニック */
#define T3_PANIC(...)               ::t3::panic("panic", __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

/*! @brief メッセージ付アサート */
#define T3_ASSERT_MSG(exp,...)      (void)((exp) || (::t3::panic(#exp, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)),0)

/*! @brief アサート */
#define T3_ASSERT(exp)              T3_ASSERT_MSG(exp, "assertion.")

/*! @brief nullチェックアサート */
#define T3_NULL_ASSERT(p)           T3_ASSERT_MSG(p != nullptr, "pointer must not be null.")

/*! @brief floatチェックアサート */
#define T3_FLOAT_ASSERT(f)          T3_ASSERT_MSG(::t3::isInvalidFloat(f), "invalid float.")

/*! @brief 範囲チェックアサート */
#define T3_ASSERT_RANGE(v, l, h)    T3_ASSERT_MSG((v >= l && v <= h), "%s is out of range. (%f <= %s(%f) <= %f)", #v, l, #v, v, h)

#define T3_RENDER_ASSERT()          T3_ASSERT(!::t3::cross::RenderSystem::isError());


#else // ENABLE_ASSERT


/*! @brief パニック */
#define T3_PANIC(...)               (void)0

/*! @brief アサート */
#define T3_ASSERT(exp)              (void)(exp)

/*! @brief メッセージ付アサート */
#define T3_ASSERT_MSG(exp, ...)     (void)(exp)

/*! @brief アサート */
#define T3_NULL_ASSERT(p)           (void)(p)

/*! @brief アサート */
#define T3_FLOAT_ASSERT(f)          (void)(f)

/*! @brief アサート */
#define T3_ASSERT_RANGE(v, l, h)    T3_ASSERT_MSG((v >= l && v <= h), "%s is out of range.", #v)

#define T3_RENDER_ASSERT()          (void)0

#endif // ENABLE_ASSERT



#endif // TRI_ASSERT_HPP_INCLUDED
