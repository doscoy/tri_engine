#ifndef PLATFORM_HPP_INCLUDED
#define PLATFORM_HPP_INCLUDED


//  WINDOWS
#ifdef WIN32
    #define PLATFORM_WINDOWS    1
#endif //   WINDOWS

//  MAC
#ifdef __APPLE__
    #define PLATFORM_MAC        1
#endif // MAC

//  iPhone
#ifdef TARGET_OS_IPHONE
    #define PLATFORM_IPHONE
#endif // iPhone


//  Android

//  Android



#if PLATFORM_MAC
    #include "osx/platform_mac.hpp"
#else
    #ifdef PLATFORM_WINDOWS
        #include "windows/platform_win.hpp"
    #endif
#endif  // PLATFORM_MAC

#include "platform_sdk.hpp"

#endif // PLATFORM_HPP_INCLUDED
