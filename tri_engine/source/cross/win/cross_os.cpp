


#include <windows.h>

#include "cross/cross_render_system.hpp"
#include "cross/cross_audio_system.hpp"
#include "cross/cross_dbg.hpp"
#include "cross/cross_os.hpp"
#include <cstdio>

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


CROSS_NS_BEGIN


void printConsole(
    const char* str
) {
    OutputDebugStringA(str);

}

std::string getDeviceFilePath() {

    return std::string("resources/");
}

CROSS_NS_END
