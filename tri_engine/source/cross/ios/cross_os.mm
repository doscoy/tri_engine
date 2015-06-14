#include <cstdio>
#import <UIKit/UIKit.h>
#include "cross_types.hpp"
#include "cross_accelerometer.hpp"
#include "cross_render_system.hpp"


t3::cross::GamePadData pad_data_[4];
t3::cross::PointingData point_data_[4];

CROSS_NS_BEGIN





bool initializePlatform(
    int width,
    int height,
    const char* const title
) {
    accelerometerInit();
    return true;
}



void terminatePlatform() {

}


void beginUpdate() {
    
    
}

void endUpdate() {
    

}

void endRender() {

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




CROSS_NS_END

