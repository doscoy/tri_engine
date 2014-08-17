#include "platform/platform.hpp"
#include "kernel/io/tri_pad.hpp"
#include "util/tri_bit.hpp"
#include "dbg/tri_assert.hpp"
#include <cstdio>

GLFWwindow* window_ = nullptr;

t3::platform::GamePadData pad_data_[4];
t3::platform::PointingData point_data_[4];


namespace {

static void callbackKeyboard(
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int mods
) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_Z) {
            t3::bitOn(pad_data_[0].button_data_, t3::Pad::BUTTON_A);
        }
        else if  (key == GLFW_KEY_X) {
            t3::bitOn(pad_data_[0].button_data_, t3::Pad::BUTTON_B);
        }
        else if  (key == GLFW_KEY_C) {
            t3::bitOn(pad_data_[0].button_data_, t3::Pad::BUTTON_X);
        }
        else if  (key == GLFW_KEY_V) {
            t3::bitOn(pad_data_[0].button_data_, t3::Pad::BUTTON_Y);
        }
        else if  (key == GLFW_KEY_LEFT) {
            t3::bitOn(pad_data_[0].button_data_, t3::Pad::BUTTON_LEFT);
        }
        else if  (key == GLFW_KEY_RIGHT) {
            t3::bitOn(pad_data_[0].button_data_, t3::Pad::BUTTON_RIGHT);
        }
        else if  (key == GLFW_KEY_UP) {
            t3::bitOn(pad_data_[0].button_data_, t3::Pad::BUTTON_UP);
        }
        else if  (key == GLFW_KEY_DOWN) {
            t3::bitOn(pad_data_[0].button_data_, t3::Pad::BUTTON_DOWN);
        }
        else if  (key == GLFW_KEY_A) {
            t3::bitOn(pad_data_[0].button_data_, t3::Pad::BUTTON_L);
        }
        else if  (key == GLFW_KEY_S) {
            t3::bitOn(pad_data_[0].button_data_, t3::Pad::BUTTON_R);
        }
        else if  (key == GLFW_KEY_SPACE) {
            t3::bitOn(pad_data_[0].button_data_, t3::Pad::BUTTON_HOME);
        }
        else if  (key == GLFW_KEY_1) {
            t3::bitOn(pad_data_[0].button_data_, t3::Pad::BUTTON_OPTION1);
        }
        else if  (key == GLFW_KEY_2) {
            t3::bitOn(pad_data_[0].button_data_, t3::Pad::BUTTON_OPTION2);
        }

        //  エスケープが押されたらアプリ終了リクエスト
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }
    else if (action == GLFW_RELEASE) {
        if (key == GLFW_KEY_Z) {
            t3::bitOff(pad_data_[0].button_data_, t3::Pad::BUTTON_A);
        }
        else if  (key == GLFW_KEY_X) {
            t3::bitOff(pad_data_[0].button_data_, t3::Pad::BUTTON_B);
        }
        else if  (key == GLFW_KEY_C) {
            t3::bitOff(pad_data_[0].button_data_, t3::Pad::BUTTON_X);
        }
        else if  (key == GLFW_KEY_V) {
            t3::bitOff(pad_data_[0].button_data_, t3::Pad::BUTTON_Y);
        }
        else if  (key == GLFW_KEY_LEFT) {
            t3::bitOff(pad_data_[0].button_data_, t3::Pad::BUTTON_LEFT);
        }
        else if  (key == GLFW_KEY_RIGHT) {
            t3::bitOff(pad_data_[0].button_data_, t3::Pad::BUTTON_RIGHT);
        }
        else if  (key == GLFW_KEY_UP) {
            t3::bitOff(pad_data_[0].button_data_, t3::Pad::BUTTON_UP);
        }
        else if  (key == GLFW_KEY_DOWN) {
            t3::bitOff(pad_data_[0].button_data_, t3::Pad::BUTTON_DOWN);
        }
        else if  (key == GLFW_KEY_A) {
            t3::bitOff(pad_data_[0].button_data_, t3::Pad::BUTTON_L);
        }
        else if  (key == GLFW_KEY_S) {
            t3::bitOff(pad_data_[0].button_data_, t3::Pad::BUTTON_R);
        }
        else if  (key == GLFW_KEY_SPACE) {
            t3::bitOff(pad_data_[0].button_data_, t3::Pad::BUTTON_HOME);
        }
        else if  (key == GLFW_KEY_1) {
            t3::bitOff(pad_data_[0].button_data_, t3::Pad::BUTTON_OPTION1);
        }
        else if  (key == GLFW_KEY_2) {
            t3::bitOff(pad_data_[0].button_data_, t3::Pad::BUTTON_OPTION2);
        }
    }
}


static void callbackMouseClick(
    GLFWwindow* window,
    int button,
    int action,
    int mods
) {
    if (button != GLFW_MOUSE_BUTTON_1) {
        return;
    }
    
    double mouse_pos_x;
    double mouse_pos_y;
    
    glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);

    t3::platform::PointingData& data = point_data_[0];
    
    if (action == GLFW_PRESS) {
        data.hit_ = true;
        data.x_ = mouse_pos_x;
        data.y_ = mouse_pos_y;
    }
    else if (action == GLFW_RELEASE) {
        data.hit_ = false;
        data.x_ = mouse_pos_x;
        data.y_ = mouse_pos_y;
    }
}


static void callbackMouseMove(
    GLFWwindow* window,
    const double x,
    const double y
) {
    t3::platform::PointingData& data = point_data_[0];
    if (!data.hit_) {
        return;
    }
    
    data.x_ = x;
    data.y_ = y;
}


}   // unname namespace

namespace t3 {
namespace platform {

void initializePlatform() {
    glfwInit();
}

void createWindow(
    const int width,
    const int height,
    const char* const title
) {

//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    
    window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
    T3_NULL_ASSERT(window_);
    glfwSwapInterval(1);
    glfwMakeContextCurrent(window_);
    
    
    glfwSetKeyCallback(window_, callbackKeyboard);
    glfwSetMouseButtonCallback(window_, callbackMouseClick);
    glfwSetCursorPosCallback(window_, callbackMouseMove);
}

void terminatePlatform() {
    glfwDestroyWindow(window_);
    glfwTerminate();
}


void beginUpdate() {
    
    
}

void endUpdate() {
    
    glfwPollEvents();
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
    return glfwWindowShouldClose(window_);
}


void printConsole(
    const char* const str
) {
    std::printf("%s", str);
}

void loadFile(
    const FilePath& file_path,
    void** data,
    size_t* size
) {

    std::ifstream fs(path);                 //ファイルオープン。読み込み形式は指定なしのときはテキストモードになる。

    T3_ASSERT(!fs.fail());
    fs.seekg( 0, std::fstream::end );       //ファイル末尾を探す
    filesize_t eof_pos = fs.tellg();        //ファイル末尾インデクスを取得
    fs.clear();
    fs.seekg( 0, std::fstream::beg );       //ファイル先頭に戻る
    filesize_t beg_pos = fs.tellg();        //ファイル先頭インデクスを取得
    size_ = eof_pos - beg_pos;              //末尾-先頭でファイルサイズを計算
    
    data_ = T3_ALLOC( size_ );
    
    fs.read( data_, size_ );                //ファイル先頭からバッファへコピー

}

}   // namespace platform
}   // namespace t3

