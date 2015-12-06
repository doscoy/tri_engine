////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

//  includes
#include "core/debug/tri_assert.hpp"
#include "core/debug/tri_trace.hpp"
#include "cross/cross_dbg.hpp"
#include "cross/cross_std.hpp"

TRI_CORE_NS_BEGIN


///
/// 浮動小数の整合性チェック
bool isInvalidFloat(const float f)
{
    //  浮動少数の無効値チェック
    if (isNan(f)) {
        return true;
    }
    if (isInf(f)) {
        return true;
    }
    //  正常な浮動少数
    return false;
}

///
/// エラーを出力して実行停止
bool panic(
    const char* const exp,
    const char* const filename,
    int line,
    const char* const funcname,
    const char* const fmt,
    ...
){


    va_list msg;
    
	char buf[256];    
	va_start( msg, fmt );
	vsnprintf(buf, 256, fmt, msg);
	va_end(msg);
    
    T3_SYSTEM_WARNING("\n");
    T3_SYSTEM_WARNING("--[ASSERTION]----------------------------\n");
    T3_SYSTEM_WARNING(" exp :%s\n", exp);
    T3_SYSTEM_WARNING(" msg :%s\n", buf);
    T3_SYSTEM_WARNING(" file:%s(%d)\n", filename, line);
    T3_SYSTEM_WARNING(" func:%s\n", funcname);
    T3_SYSTEM_WARNING("-----------------------------------------\n");

    CROSS_PANIC();
}


TRI_CORE_NS_END