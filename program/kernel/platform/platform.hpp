#ifndef PLATFORM_HPP_INCLUDED
#define PLATFORM_HPP_INCLUDED



#if WIN32
    #define PLATFORM_WINDOWS    1
#endif //   WIN32

#if 0
    #define PLATFORM_MAC        1
#endif

#if PLATFORM_MAC
    #include "osx/platform_mac.hpp"
#else
    #ifdef PLATFORM_WINDOWS
        #include "windows/platform_win.hpp"
    #endif
#endif  // PLATFORM_MAC

#include "platform_sdk.hpp"

#endif // PLATFORM_HPP_INCLUDED
