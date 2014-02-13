#include "platform.hpp"




GLFWwindow* window_ = nullptr;

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
    window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwSwapInterval(1);
    glfwMakeContextCurrent(window_);

}

void terminatePlatform() {
    glfwDestroyWindow(window_);
    glfwTerminate();
}


void beginMainLoop() {
    
    
}

void endMainLoop() {
    
    glfwPollEvents();
}

void getPlatformPadData(
    int pad_num,
    GamePadData* data
) {
    
    
}

bool isExitRequest() {
    return glfwWindowShouldClose(window_);
}

}   // namespace platform
}   // namespace t3

