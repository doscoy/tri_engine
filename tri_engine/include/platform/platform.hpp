#ifndef PLATFORM_HPP_INCLUDED
#define PLATFORM_HPP_INCLUDED


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
    int no,
    GamePadData* data
);

void getPlatformPointingData(
    int no,
    PointingData* data
);

bool isExitRequest();

void printConsole(
    const char* const str
);

}   // namespace platform
}   // namespace t3

#endif // PLATFORM_HPP_INCLUDED
