
#include "cross/cross_render_system.hpp"
#include "cross/cross_audio_system.hpp"
#include "cross/cross_dbg.hpp"
#include "cross/cross_os.hpp"
#include "cross/cross_std.hpp"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


//  GLFWを使ったOS依存の処理はまとめてある
#include "../common/cross_os_glfw.cpp"


//  windows.hは内部でIN OUT min maxなどの非常に一般的な名前をdefineのシンボルとして
//  使っているのでTriENGINE側のソースに悪影響を及ぼすケースがある。なので最後にインクルードする
#include <windows.h>


CROSS_NS_BEGIN

///
/// デバッグ出力
void printConsole(
    const char* str
) {
    //  VSの出力ウィンドウへ
    OutputDebugStringA(str);

}

///
/// システム固有のパスを返す
std::string getDeviceFilePath() {

    constexpr int STR_SIZE = 256;
    wchar_t win_current_dir_w[STR_SIZE];
    //  Windowsの場合はカレントディレクトリを返す
    GetCurrentDirectory(STR_SIZE, win_current_dir_w);

    char win_current_dir_utf[STR_SIZE];
    wcstombs(win_current_dir_utf, win_current_dir_w, STR_SIZE);

    //  \を/に変換
    std::regex re(R"(\\)");
    std::string text(win_current_dir_utf);
    std::string conv_text = std::regex_replace(text, re, "/");
    std::string result_path = conv_text + std::string("/resources/");
    return result_path;
}

CROSS_NS_END
