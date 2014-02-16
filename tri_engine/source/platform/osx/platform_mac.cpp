#include "platform.hpp"
#include "kernel/io/tri_pad.hpp"
#include "util/tri_bit.hpp"


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
    window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
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


void beginMainLoop() {
    
    
}

void endMainLoop() {
    
    glfwPollEvents();
}

void getPlatformPadData(
    int no,
    GamePadData* data
) {
    *data = pad_data_[no];
}

void getPlatformPointingData(
    int no,
    PointingData* data
) {
    *data = point_data_[no];
}



bool isExitRequest() {
    return glfwWindowShouldClose(window_);
}

}   // namespace platform
}   // namespace t3
