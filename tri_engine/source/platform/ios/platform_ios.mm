#include "platform.hpp"
#include "kernel/io/tri_pad.hpp"
#include "util/tri_bit.hpp"
#include <cstdio>
#include "base/tri_application.hpp"
#include "dbg/tri_assert.hpp"


t3::platform::GamePadData pad_data_[4];
t3::platform::PointingData point_data_[4];

t3::Application* app_ = nullptr;


extern int iosMain(int argc, char** argv);

namespace t3 {
inline namespace platform {


void run(int argc, char** argv, t3::Application* app) {
    app_ = app;
    iosMain(argc, argv);
}


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



void loadFile(
    const FilePath& file_path,
    uint8_t** data,
    size_t* size
) {
    const char* filename = file_path.getFileNameNotExt().c_str();
    NSString* nsfilename = [NSString stringWithCString: filename encoding:NSUTF8StringEncoding];

    const char* extname = file_path.getExt().c_str();
    NSString* nsextname = [NSString stringWithCString: extname encoding:NSUTF8StringEncoding];


    NSBundle* bundle = [NSBundle mainBundle];
    NSString* path = [bundle pathForResource:nsfilename ofType:nsextname];
    NSData* nsdata = [[NSData alloc] initWithContentsOfFile:path];
    T3_NULL_ASSERT(nsdata);
    *data = (uint8_t*)[nsdata bytes];
    *size = [nsdata length];
}

}   // namespace platform
}   // namespace t3

