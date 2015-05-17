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
#if DEBUG

    return std::string("/Users/kani/project/tri_engine/samples/resources/");

#else
    return std::string("");
#endif
}

}   // namespace cross
