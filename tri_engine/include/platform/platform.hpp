#ifndef PLATFORM_HPP_INCLUDED
#define PLATFORM_HPP_INCLUDED


#include "platform_sdk.hpp"
#include "platform_types.hpp"
#include "kernel/io/tri_filepath.hpp"

namespace t3 {

inline namespace base {
class Application;
}   // namespace base




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
void platformPadData(
    int no,
    GamePadData* data
);

void platformPointingData(
    int no,
    PointingData* data
);


void platformAcceleromator(
    int no,
    AccelerometerData* data
);

bool isExitRequest();

void printConsole(
    const char* const str
);

std::string getDeviceFilePath();

void loadFile(
    const FilePath& file_path,
    uint8_t** data,
    size_t* size
);

void saveInteger(
    const char* const label,
    int val
);

void loadInteger(
    const char* const label,
    int* key
);







}   // namespace platform
}   // namespace t3

#endif // PLATFORM_HPP_INCLUDED
