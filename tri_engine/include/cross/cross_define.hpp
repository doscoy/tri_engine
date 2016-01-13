////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file cross_define.hpp
    クロスプラットフォームに対処するための各種定義.
*/

#ifndef PLATFORM_SDK_HPP_INCLUDED
#define PLATFORM_SDK_HPP_INCLUDED


#define TRI_VERSION_ECHO    0


#define CROSS_TARGET_PLATFORM_WIN32     (2)
#define CROSS_TARGET_PLATFORM_OSX       (3)
#define CROSS_TARGET_PLATFORM_IOS       (4)

#if defined(_WIN32)

    #define CROSS_TARGET_PLATFORM       CROSS_TARGET_PLATFORM_WIN32
	#define CROSS_TARGET_COMPILER_MSVC

#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #include <unistd.h>

    //  iOS device
    #if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#if TRI_VERSION_ECHO
        #warning "target ios"
#endif
        #define CROSS_TARGET_PLATFORM       CROSS_TARGET_PLATFORM_IOS

        #ifdef __i386__
#if TRI_VERSION_ECHO
            #warning "ios sim 32bit"
#endif
            #define CROSS_TARGET_IOS_SIMULATER    1
        #endif // __i386__

        #ifdef __x86_64
#if TRI_VERSION_ECHO
            #warning "ios sim 64bit"
#endif
            #define CROSS_TARGET_IOS_SIMULATER    1
        #endif

        #ifdef PNG_ARM_NEON
#if TRI_VERSION_ECHO
            #warning "png neon"
#endif
        #endif

    //  MAC
    #else
        #define CROSS_TARGET_PLATFORM       CROSS_TARGET_PLATFORM_OSX
        #warning "target osx"

    #endif

	#define CROSS_TARGET_COMPILER_CLANG

#endif

//  コンパイラバージョン
#if defined(CROSS_TARGET_COMPILER_MSVC)
	#define CROSS_WEAK_SIMBOL 

#elif defined(CROSS_TARGET_COMPILER_CLANG)

	#define CROSS_WEAK_SIMBOL  __attribute__((weak))

#endif

//  OpenGLバージョン
#define CROSS_GL_40  400
#define CROSS_GL_ES2  20
#define CROSS_GL_ES3  30

#if CROSS_TARGET_PLATFORM == CROSS_TARGET_PLATFORM_WIN32
    #define CROSS_GL_VERSION    CROSS_GL_40
#if TRI_VERSION_ECHO
    #warning "target gl4"
#endif
#elif CROSS_TARGET_PLATFORM == CROSS_TARGET_PLATFORM_OSX
    #define CROSS_GL_VERSION    CROSS_GL_40
#if TRI_VERSION_ECHO
    #warning "target gl4"
#endif
#else
    #define CROSS_GL_VERSION    CROSS_GL_ES3
#if TRI_VERSION_ECHO
    #warning "target gles3"
#endif
#endif


#endif // PLATFORM_SDK_HPP_INCLUDED