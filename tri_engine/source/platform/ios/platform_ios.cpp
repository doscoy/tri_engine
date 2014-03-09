#include "platform.hpp"
#include "kernel/io/tri_pad.hpp"
#include "util/tri_bit.hpp"
#include <cstdio>


t3::platform::GamePadData pad_data_[4];
t3::platform::PointingData point_data_[4];


namespace {



}   // unname namespace

namespace t3 {
namespace platform {

void initializePlatform() {

}

void createWindow(
    const int width,
    const int height,
    const char* const title
) {

}

void terminatePlatform() {

}


void beginUpdate() {
    
    
}

void endUpdate() {
    

}

void getPlatformPadData(
    int no,
    GamePadData* data
) {
    *data = pad_data_[no];
}

void getPlatformPointingData(
    int no,
    PointingData* data
) {
    *data = point_data_[no];
}



bool isExitRequest() {
    return false;
}


void printConsole(
    const char* const str
) {
    std::printf("%s", str);
}


}   // namespace platform
}   // namespace t3

