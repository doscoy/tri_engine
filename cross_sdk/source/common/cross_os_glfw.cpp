
#include "cross_glfw.hpp"
#include "cross_os.hpp"
#include "cross_audio_system.hpp"
#include "cross_render_system.hpp"
#include "cross_dbg.hpp"

namespace {

GLFWwindow* window_ = nullptr;
float window_width_;
float window_height_;
float half_width_;
float half_height_;


}   // unname namespace

namespace cross {



uint32_t padEmulateKeyboard() {
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
    return button_bit;
}




bool initializePlatform(
    int w,
    int h,
    const char* title
) {

    if (!glfwInit()) {
        //  glfw初期化失敗
        CROSS_PANIC();
    }
    
    // ------------------------------------------------
    //  glfwを使う設定
    //  GLのバージョン
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

    //  ウィンドウリサイズ設定
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    //  デプスバッファビット深度
    glfwWindowHint(GLFW_DEPTH_BITS, 16);

    //  API設定
//    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API); // GLFW_OPENGL_API or GLFW_OPENGL_ES_API

    //  コアプロファイル
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if (window_) {
        glfwMakeContextCurrent(window_);
    } else {
        return false;
    }

    glewExperimental = true;
    GLenum init_result = glewInit();
    glGetError();

    if ( init_result != GLEW_OK ) {
		std::cout << "error: " << glewGetErrorString( init_result ) << std::endl;
        return false;
	}



    //  スクリーンサイズを覚えておく
    window_width_ = w;
    window_height_ = h;
    half_width_ = w / 2;
    half_height_ = h / 2;

    //  オーディオシステムの初期化
    AudioSystem::initializeAudioSystem();

    return true;

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

    
//    timespec  req = {0, 1000000};
//    nanosleep(&req, 0);
}

void platformPadData(
    int no,
    GamePadData* data
) {
    data->button_data_ = 0;
    
    if (no > 0) {
        return;
    }
    
    uint32_t button_bit = padEmulateKeyboard();

    if (glfwJoystickPresent(GLFW_JOYSTICK_1) == GL_TRUE) {
        int button_count = 0;
        auto button_state = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &button_count);
        
//        printf("btn cnt %d\n", button_count);
//        for (int i = 0; i < button_count; ++i) {
//            printf("btn[%d] %d  ", i, button_state[i]);
//        }
        
        if (button_count > 0 && button_state[0]) {
            button_bit |= cross::PAD_BUTTON_UP;
        }
        if (button_count > 1 && button_state[1]) {
            button_bit |= cross::PAD_BUTTON_DOWN;
        }
        if (button_count > 2 && button_state[2]) {
            button_bit |= cross::PAD_BUTTON_LEFT;
        }
        if (button_count > 3 && button_state[3]) {
            button_bit |= cross::PAD_BUTTON_RIGHT;
        }
        if (button_count > 4 && button_state[4]) {
            button_bit |= cross::PAD_BUTTON_OPTION1;
        }
        if (button_count > 5 && button_state[5]) {
            button_bit |= cross::PAD_BUTTON_OPTION2;
        }

        if (button_count > 8 && button_state[8]) {
            button_bit |= cross::PAD_BUTTON_L;
        }
        if (button_count > 9 && button_state[9]) {
            button_bit |= cross::PAD_BUTTON_R;
        }
        if (button_count > 10 && button_state[10]) {
            button_bit |= cross::PAD_BUTTON_HOME;
        }

        if (button_count > 11 && button_state[11]) {
            button_bit |= cross::PAD_BUTTON_A;
        }
        if (button_count > 12 && button_state[12]) {
            button_bit |= cross::PAD_BUTTON_B;
        }
        if (button_count > 13 && button_state[13]) {
            button_bit |= cross::PAD_BUTTON_X;
        }
        if (button_count > 14 && button_state[14]) {
            button_bit |= cross::PAD_BUTTON_Y;
        }
        
        int stick_count = 0;
        auto stick_axis = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &stick_count);

        printf("stick cnt %d\n", stick_count);
        for (int i = 0; i < button_count; ++i) {
            printf("stk[%d] %f  ", i, stick_axis[i]);
        }
        
        if (stick_count > 0) {
            data->stick1x_ = stick_axis[0];
        }
        if (stick_count > 1) {
            data->stick1y_ = stick_axis[1];
        }
        if (stick_count > 2) {
            data->stick2x_ = stick_axis[2];
        }
        if (stick_count > 3) {
            data->stick2y_ = stick_axis[3];
        }
        if (stick_count > 4) {
            data->trigger_l_ = (stick_axis[4] + 1.0f) * 0.5f;
        }
        if (stick_count > 5) {
            data->trigger_r_ = (stick_axis[5] + 1.0f) * 0.5f;
        }

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

}   // namespace cross