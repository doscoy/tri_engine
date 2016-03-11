
#include "cross/cross_render_system.hpp"
#include "cross/cross_audio_system.hpp"
#include "cross/cross_dbg.hpp"
#include "cross/cross_os.hpp"
#include "cross/cross_std.hpp"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


//  GLFW���g����OS�ˑ��̏����͂܂Ƃ߂Ă���
#include "../common/cross_os_glfw.cpp"


//  windows.h�͓�����IN OUT min max�Ȃǂ̔��Ɉ�ʓI�Ȗ��O��define�̃V���{���Ƃ���
//  �g���Ă���̂�TriENGINE���̃\�[�X�Ɉ��e�����y�ڂ��P�[�X������B�Ȃ̂ōŌ�ɃC���N���[�h����
#include <windows.h>


CROSS_NS_BEGIN

///
/// �f�o�b�O�o��
void printConsole(
    const char* str
) {
    //  VS�̏o�̓E�B���h�E��
    OutputDebugStringA(str);

}

///
/// �V�X�e���ŗL�̃p�X��Ԃ�
std::string getDeviceFilePath() {

    constexpr int STR_SIZE = 256;
    wchar_t win_current_dir_w[STR_SIZE];
    //  Windows�̏ꍇ�̓J�����g�f�B���N�g����Ԃ�
    GetCurrentDirectory(STR_SIZE, win_current_dir_w);

    char win_current_dir_utf[STR_SIZE];
    wcstombs(win_current_dir_utf, win_current_dir_w, STR_SIZE);

    //  \��/�ɕϊ�
    std::regex re(R"(\\)");
    std::string text(win_current_dir_utf);
    std::string conv_text = std::regex_replace(text, re, "/");
    std::string result_path = conv_text + std::string("/resources/");
    return result_path;
}

CROSS_NS_END
