#include <cstdio>
#import <UIKit/UIKit.h>
#include "cross_types.hpp"
#include "cross_accelerometer.hpp"
#include "cross_render_system.hpp"

cross::GamePadData pad_data_[4];
cross::PointingData point_data_[4];



namespace cross {






void initializePlatform(
    int width,
    int height,
    const char* const title
) {
    accelerometerInit();
}



void terminatePlatform() {

}


void beginUpdate() {
    
    
}

void endUpdate() {
    

}

void endRender() {

    cross::RenderSystem::swapBuffers();
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


bool isExitRequest() {
    return false;
}


void printConsole(
    const char* const str
) {
    std::printf("%s", str);
}

void breakpoint() {

}

std::string getDeviceFilePath() {
    NSString* readPath = [NSString stringWithFormat:@"%@%@", [[NSBundle mainBundle] bundlePath], @"/"];
    std::string path =[readPath UTF8String];

    return path;
}


void loadFile(
    const char* const file_path,
    uint8_t** data,
    size_t* size
) {
/*
    NSString* nsextname = [NSString stringWithCString: file_path encoding:NSUTF8StringEncoding];


    NSBundle* bundle = [NSBundle mainBundle];
    NSString* path = [bundle pathForResource:nsfilename ofType:nsextname];
    NSData* nsdata = [[NSData alloc] initWithContentsOfFile:path];
    T3_NULL_ASSERT(nsdata);
    *size = [nsdata length];
    
    *data = (uint8_t*)T3_SYS_ALLOC(*size);
    const void* nsbytes = [nsdata bytes];
    std::memcpy(*data, nsbytes, *size);
*/
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

    *val = static_cast<int>(nsval);
}





}   // namespace cross

