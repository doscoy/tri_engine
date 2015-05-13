
#include "cross_os.hpp"
#include "cstdio"

#include <glfw3.h>

namespace {

GLFWwindow* window_ = nullptr;
}

namespace cross {

void initializePlatform() {

    glfwInit();
    window_ = glfwCreateWindow(640, 480, "mytesz", nullptr, nullptr);
    glfwMakeContextCurrent(window_);
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

}

void platformPointingData(
    int no,
    PointingData* data
) {


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

    return std::string();
}

}   // namespace cross
