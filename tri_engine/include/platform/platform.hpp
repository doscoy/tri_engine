#ifndef PLATFORM_HPP_INCLUDED
#define PLATFORM_HPP_INCLUDED


#if defined(_WIN32)
    //  WINDOWS
    #define PLATFORM_WINDOWS    1

#elif defined(__APPLE__)
    //  MAC
    #define PLATFORM_MAC        1

#elif defined(TARGET_OS_IPHONE)
    //  iPhone
    #define PLATFORM_IPHONE
#endif // iPhone



#include "platform_sdk.hpp"
#include "platform_types.hpp"



namespace t3 {
namespace platform {

void initializePlatform();
void createWindow(
    const int width,
    const int height,
    const char* const title
);
void terminatePlatform();
void beginMainLoop();
void endMainLoop();
void getPlatformPadData(
    int pad_num,
    GamePadData* data
);

bool isExitRequest();

}   // namespace platform
}   // namespace t3

#endif // PLATFORM_HPP_INCLUDED
