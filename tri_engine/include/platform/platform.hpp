#ifndef PLATFORM_HPP_INCLUDED
#define PLATFORM_HPP_INCLUDED


#include "platform_sdk.hpp"
#include "platform_types.hpp"
#include "kernel/io/tri_filepath.hpp"


namespace t3 {
inline namespace base {
class Application;
}   // inline namespace
inline namespace platform {

void initializePlatform();

void run(
    int argc,
    char** argv,
    Application* app
);

void createWindow(
    const int width,
    const int height,
    const char* const title
);
void terminatePlatform();
void beginUpdate();
void endUpdate();
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

std::string getDeviceFilePath(
    std::string filename,
    std::string extname
);

void loadFile(
    const FilePath& file_path,
    uint8_t** data,
    size_t* size
);
    
}   // namespace platform
}   // namespace t3

#endif // PLATFORM_HPP_INCLUDED
