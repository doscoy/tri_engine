#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "cross_os.hpp"
#include "cstdio"


namespace {

GLFWwindow* window_ = nullptr;
}

namespace cross {

void initializePlatform(
    int w,
    int h,
    const char* title
) {
    glfwInit();
    window_ = glfwCreateWindow(w, h, title, nullptr, nullptr);
    glfwMakeContextCurrent(window_);
    glewInit();

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
    data->x_ = x;
    data->y_ = y;
    
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
