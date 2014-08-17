#include "platform/platform.hpp"
#include "kernel/io/tri_pad.hpp"
#include "util/tri_bit.hpp"
#include <cstdio>
#include "base/tri_application.hpp"
#include "dbg/tri_assert.hpp"
#include "kernel/memory/tri_memory.hpp"
#import <UIKit/UIKit.h>


t3::platform::GamePadData pad_data_[4];
t3::platform::PointingData point_data_[4];
t3::platform::AccelerometerData acc_data_[4];



extern int iosMain(int argc, char** argv, t3::Application* app);


namespace  {



}   //  unname namespace





namespace t3 {
inline namespace platform {


void run(int argc, char** argv, t3::Application* app) {
    iosMain(argc, argv, app);
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

void platformPadData(
    int no,
    GamePadData* data
) {
    *data = pad_data_[no];
}

void platformPointingData(
    int no,
    PointingData* data
) {
    *data = point_data_[no];
}

void platformAcceleromator(
    int no,
    AccelerometerData* data
) {
    *data = acc_data_[no];
}

bool isExitRequest() {
    return false;
}


void printConsole(
    const char* const str
) {
    std::printf("%s", str);
}



std::string getDeviceFilePath() {
    NSString* readPath = [NSString stringWithFormat:@"%@%@", [[NSBundle mainBundle] bundlePath], @"/"];
    std::string path =[readPath UTF8String];

    return path;
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
    *size = [nsdata length];
    
    *data = (uint8_t*)T3_ALLOC(*size);
    const void* nsbytes = [nsdata bytes];
    std::memcpy(*data, nsbytes, *size);
}

void saveInteger(
    const char* const key,
    int val
) {
    NSString* nskey = [NSString stringWithCString: key encoding:NSUTF8StringEncoding];
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    [defaults setInteger:val forKey:nskey];
}

void loadInteger(
    const char* const key,
    int* val
) {
    NSString* nskey = [NSString stringWithCString: key encoding:NSUTF8StringEncoding];
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSInteger nsval = [defaults integerForKey:nskey];

    *val = nsval;
}





}   // namespace platform
}   // namespace t3

