/**
    @file cross_define.hpp
    クロスプラットフォームに対処するための各種定義.
*/

#ifndef PLATFORM_SDK_HPP_INCLUDED
#define PLATFORM_SDK_HPP_INCLUDED





#if defined(_WIN32)

    #define CROSS_TARGET_PLATFORM_WIN32
	#define CROSS_TARGET_COMPILER_MSVC

#elif defined(__APPLE__)
    //  iOS device
    #if defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
        #warning "target ios"
        #define CROSS_TARGET_PLATFORM_IOS     1

        #ifdef __i386__
            #warning "ios sim 32bit"
            #define CROSS_TARGET_IOS_SIMULATER    1
        #endif // __i386__

        #ifdef __x86_64
            #warning "ios sim 64bit"
            #define CROSS_TARGET_IOS_SIMULATER    1
        #endif

        #ifdef PNG_ARM_NEON
            #warning "png neon"
        #endif

    //  MAC
    #else
//        #warning "target mac"
//        #include "png.h"
//        #include <OpenGL/OpenGL.h>
//        #include "GLFW/glfw3.h"
//        #define PLATFORM_MAC
        
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

#if defined(CROSS_TARGET_PLATFORM_WIN32)
    #define CROSS_GL_VERSION    CROSS_GL_40
#elif defined(CROSS_TARGET_PLATFORM_OSX)
    #define CROSS_GL_VERSION    CROSS_GL_40

#else
    #define CROSS_GL_VERSION    CROSS_GL_ES2

#endif


#endif // PLATFORM_SDK_HPP_INCLUDED