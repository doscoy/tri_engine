/**
    @file cross_define.hpp
    クロスプラットフォームに対処するための各種定義.
*/

#ifndef PLATFORM_SDK_HPP_INCLUDED
#define PLATFORM_SDK_HPP_INCLUDED



#define CROSS_TARGET_PLATFORM_WIN32     (2)
#define CROSS_TARGET_PLATFORM_OSX       (3)
#define CROSS_TARGET_PLATFORM_IOS       (4)

#if defined(_WIN32)

    #define CROSS_TARGET_PLATFORM       CROSS_TARGET_PLATFORM_WIN32
	#define CROSS_TARGET_COMPILER_MSVC

#elif defined(__APPLE__)
    #include <TargetConditionals.h>

    //  iOS device
    #if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
        #warning "target ios"
        #define CROSS_TARGET_PLATFORM       CROSS_TARGET_PLATFORM_IOS

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
//    #warning "target gl4"

#elif CROSS_TARGET_PLATFORM == CROSS_TARGET_PLATFORM_OSX
    #define CROSS_GL_VERSION    CROSS_GL_40
    #warning "target gl4"

#else
    #define CROSS_GL_VERSION    CROSS_GL_ES2
    #warning "target gles2"

#endif


#endif // PLATFORM_SDK_HPP_INCLUDED