


#include <windows.h>

#include "cross_render_system.hpp"
#include "cross_audio_system.hpp"
#include "cross_dbg.hpp"
#include "cross_os.hpp"
#include "cstdio"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


namespace cross {

bool initializePlatform(
    int w,
    int h,
    const char* title
) {
    //  オーディオシステムの初期化
    AudioSystem::initializeAudioSystem();

    return RenderSystem::initialize(w, h, title);
}


void terminatePlatform() {
    RenderSystem::terminate();
}

void beginUpdate() {

}

void endUpdate() {
}


void endRender() {
    RenderSystem::swapBuffers();
}

void platformPadData(
    int no,
    GamePadData* data
) {

}

void platformPointingData(
    int no,
    PointingData* data
) {


}

bool isExitRequest() {

    if (RenderSystem::isExitRequest()) {
        return true;
    }

    return false;
}

void printConsole(
    const char* const str
) {
    OutputDebugStringA(str);

}

std::string getDeviceFilePath() {

    return std::string("resources/");
}

}   // namespace cross
