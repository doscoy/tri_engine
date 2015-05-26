#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "cross_os.hpp"
#include "cstdio"
#include <sys/time.h>


namespace {

GLFWwindow* window_ = nullptr;
float window_width_;
float window_height_;
float half_width_;
float half_height_;
}

namespace cross {

void initializePlatform(
    int w,
    int h,
    const char* title
) {
    //  システム初期化
    glfwInit();
    window_ = glfwCreateWindow(w, h, title, nullptr, nullptr);
    glfwMakeContextCurrent(window_);
    glewInit();
    
    //  スクリーンサイズを覚えておく
    window_width_ = w;
    window_height_ = h;
    half_width_ = w / 2;
    half_height_ = h / 2;
}


void terminatePlatform() {

    glfwTerminate();
}

void beginUpdate() {

}

void endUpdate() {

}


void endRender() {

    glfwSwapBuffers(window_);
    glfwPollEvents();
    timespec  req = {0, 1000000};
    nanosleep(&req, 0);
}

void platformPadData(
    int no,
    GamePadData* data
) {
    if (no > 0) {
        return;
    }
    uint32_t button_bit = 0;

    if (glfwGetKey(window_, GLFW_KEY_UP) == GLFW_PRESS) {
        button_bit |= PAD_BUTTON_UP;
    }
    if (glfwGetKey(window_, GLFW_KEY_DOWN) == GLFW_PRESS) {
        button_bit |= PAD_BUTTON_DOWN;
    }
    if (glfwGetKey(window_, GLFW_KEY_LEFT) == GLFW_PRESS) {
        button_bit |= PAD_BUTTON_LEFT;
    }
    if (glfwGetKey(window_, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        button_bit |= PAD_BUTTON_RIGHT;
    }
    if (glfwGetKey(window_, GLFW_KEY_Z) == GLFW_PRESS) {
        button_bit |= PAD_BUTTON_A;
    }
    if (glfwGetKey(window_, GLFW_KEY_X) == GLFW_PRESS) {
        button_bit |= PAD_BUTTON_B;
    }
    if (glfwGetKey(window_, GLFW_KEY_C) == GLFW_PRESS) {
        button_bit |= PAD_BUTTON_X;
    }
    if (glfwGetKey(window_, GLFW_KEY_V) == GLFW_PRESS) {
        button_bit |= PAD_BUTTON_Y;
    }
    if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) {
        button_bit |= PAD_BUTTON_L;
    }
    if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) {
        button_bit |= PAD_BUTTON_R;
    }
    if (glfwGetKey(window_, GLFW_KEY_SPACE) == GLFW_PRESS) {
        button_bit |= PAD_BUTTON_HOME;
    }
    if (glfwGetKey(window_, GLFW_KEY_1) == GLFW_PRESS) {
        button_bit |= PAD_BUTTON_DEBUG1;
    }
    if (glfwGetKey(window_, GLFW_KEY_2) == GLFW_PRESS) {
        button_bit |= PAD_BUTTON_DEBUG2;
    }
    if (glfwGetKey(window_, GLFW_KEY_3) == GLFW_PRESS) {
        button_bit |= PAD_BUTTON_DEBUG3;
    }
    
    data->button_data_ = button_bit;
}

void platformPointingData(
    int no,
    PointingData* data
) {
    if (no > 0) {
        return;
    }
    
    double x, y;
    glfwGetCursorPos(window_, &x, &y);
    
    data->x_ = (x - half_width_) / half_width_;
    data->y_ = -((y - half_height_) / half_height_);
    
    data->hit_ = (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) != 0);

}

bool isExitRequest() {

    return glfwWindowShouldClose(window_);
}

void printConsole(
    const char* const str
) {
    std::printf(str);
}

std::string getDeviceFilePath() {
#if DEBUG

    return std::string("/Users/kani/project/tri_engine/samples/resources/");

#else
    return std::string("");
#endif
}





}   // namespace cross
