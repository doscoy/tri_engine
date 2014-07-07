#ifndef PLATFORM_SDK_HPP_INCLUDED
#define PLATFORM_SDK_HPP_INCLUDED

#include <cstdint>

#if defined(_WIN32)

    #warning "target win32"
    #define PLATFORM_WIN32


#elif defined(__APPLE__)
    //  iOS device
    #if defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
        #warning "target ios"
        #include "png.h"
        #include <OpenGLES/ES2/gl.h>
        #include <OpenAL/al.h>
        #include <OpenAL/alc.h>
        #define PLATFORM_IOS

        #ifdef __i386__
            #warning "ios sim 32bit"
            #define IOS_SIMULATER
        #endif // __i386__

        #ifdef __x86_64
            #warning "ios sim 64bit"
            #define IOS_SIMULATER
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

#endif


#endif // PLATFORM_SDK_HPP_INCLUDED