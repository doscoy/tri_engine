#include <glew.h>

#include "cross_os.hpp"
#include "cstdio"

#include <glfw3.h>
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

    GLenum init_result = glewInit();

    if ( init_result != GLEW_OK ) {
		std::cout << "error: " << glewGetErrorString( init_result ) << std::endl;
	}

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
