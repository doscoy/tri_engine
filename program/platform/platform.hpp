#ifndef PLATFORM_HPP_INCLUDED
#define PLATFORM_HPP_INCLUDED

#define PLATFORM_MAC        1
//#define PLATFORM_WINDOWS    1

#if PLATFORM_MAC
    #include "platform_mac.hpp"
#else
    #ifdef PLATFORM_WINDOWS
        #include "platform_win.hpp"
    #endif
#endif  // PLATFORM_MAC

#endif // PLATFORM_HPP_INCLUDED
