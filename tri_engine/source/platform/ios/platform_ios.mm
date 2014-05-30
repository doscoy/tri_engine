#include "platform.hpp"
#include "kernel/io/tri_pad.hpp"
#include "util/tri_bit.hpp"
#include <cstdio>
#include "base/tri_application.hpp"
#include "dbg/tri_assert.hpp"
#include "kernel/memory/tri_memory.hpp"
#include "platform/ios/ViewController.hpp"

#import "GADBannerView.h"

t3::platform::GamePadData pad_data_[4];
t3::platform::PointingData point_data_[4];
t3::platform::AccelerometerData acc_data_[4];

t3::Application* app_ = nullptr;
extern GADBannerView* banner_view_;

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

void getPlatformAcceleData(
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



std::string getDeviceFilePath(
    std::string filename,
    std::string extname
) {
    NSString* nsfilename = [NSString stringWithCString: filename.c_str() encoding:NSUTF8StringEncoding];
    NSString* nsextname = [NSString stringWithCString: extname.c_str() encoding:NSUTF8StringEncoding];
    
    
    NSBundle* bundle = [NSBundle mainBundle];
    NSString* path = [bundle pathForResource:nsfilename ofType:nsextname];
    
    std::string str = [path UTF8String];
    return str;
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


void showAd() {
    banner_view_.hidden = NO;
}

void hideAd() {
    banner_view_.hidden = YES;
}

void showNetworkRanking() {
 
    
    
    ViewController* topController = [UIApplication sharedApplication].keyWindow.rootViewController;
    while (topController.presentedViewController) {
        topController = topController.presentedViewController;
    }
    
    
    [topController showRanking];
    
    
}

bool isEnableNetworkRanking() {
    if ([GKLocalPlayer localPlayer].isAuthenticated) {
        return true;
    }
    else {
        return false;
    }
}

void sendRankingScore(
    int score
) {
    GKScore* gkscore = [[GKScore alloc] initWithLeaderboardIdentifier:@"com.aquariuscode.star01.lb"];
    gkscore.value = score;
    [GKScore reportScores:@[gkscore] withCompletionHandler:^(NSError *error) {
        if (error) {
            // エラーの場合
        }
    }];
}



}   // namespace platform
}   // namespace t3

