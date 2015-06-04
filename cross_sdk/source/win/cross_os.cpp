


#include <windows.h>

#include "cross_render_system.hpp"
#include "cross_audio_system.hpp"
#include "cross_dbg.hpp"
#include "cross_os.hpp"
#include "cstdio"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


namespace cross {


void printConsole(
    const char* const str
) {
    OutputDebugStringA(str);

}

std::string getDeviceFilePath() {

    return std::string("resources/");
}

}   // namespace cross
