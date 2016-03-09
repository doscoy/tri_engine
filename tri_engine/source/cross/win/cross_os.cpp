


#include <windows.h>

#include "cross/cross_render_system.hpp"
#include "cross/cross_audio_system.hpp"
#include "cross/cross_dbg.hpp"
#include "cross/cross_os.hpp"
#include <cstdio>
#include "cross/cross_std.hpp"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


CROSS_NS_BEGIN


void printConsole(
    const char* str
) {
    OutputDebugStringA(str);

}

std::string getDeviceFilePath() {
    constexpr int STR_SIZE = 256;
    wchar_t win_current_dir_w[STR_SIZE];
    GetCurrentDirectory(STR_SIZE, win_current_dir_w);

    char win_current_dir_utf[STR_SIZE];
    wcstombs(win_current_dir_utf, win_current_dir_w, STR_SIZE);

    //  \‚ð/‚É•ÏŠ·
    std::regex re(R"(\\)");
    std::string text(win_current_dir_utf);
    std::string conv_text = std::regex_replace(text, re, "/");
    std::string result_path = conv_text + std::string("/resources/");
    return result_path;
}

CROSS_NS_END
