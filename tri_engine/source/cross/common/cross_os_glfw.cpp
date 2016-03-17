
#include "cross/cross_glfw.hpp"
#include "cross/cross_os.hpp"
#include "cross/cross_audio_system.hpp"
#include "cross/cross_render_system.hpp"
#include "cross/cross_dbg.hpp"


//#include "core/kernel/io/tri_file.hpp"
#include "cross/cross_std.hpp"
#include "core/core_config.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "core/base/tri_types.hpp"
#include "core/kernel/io/tri_filepath.hpp"

#include "core/base/tri_screen_manager.hpp"
#include "core/base/tri_director.hpp"

namespace {

GLFWwindow* window_ = nullptr;


}   // unname namespace

CROSS_NS_BEGIN

/// ウィンドウリサイズ時のコールバック
///     ウィンドウサイズが変更された時に呼ばれる
void windowResizeCallback(
    GLFWwindow* window, // リサイズされたウィンドウ
    int width,          // 新しい幅
    int height          // 新しい高さ
) {

    auto& screen_mgr = t3::ScreenManager::instance();
    Vec2 new_size(width, height);
    screen_mgr.resizeScreen(new_size);

    auto& director = t3::Director::instance();
    director.setupFinalLayer();
}


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
    const InitConfiguration& config
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
    if (config.window_resizable_) {
        //  リサイズ許可
        glfwWindowHint(GLFW_RESIZABLE, true);
    } else {
        //  リサイズ禁止
        glfwWindowHint(GLFW_RESIZABLE, false);

    }


    //  デプスバッファビット深度
    glfwWindowHint(GLFW_DEPTH_BITS, 16);

    //  API設定
//    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API); // GLFW_OPENGL_API or GLFW_OPENGL_ES_API

    //  コアプロファイル
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ----------------------------------------
    //  window生成
    float w = config.window_width_;
    float h = config.window_height_;
    GLFWmonitor* monitor = nullptr;
    if (config.full_screen_) {
        monitor = glfwGetPrimaryMonitor();
    }

    //  生成
    window_ = glfwCreateWindow(
        w, h, 
        config.title_, 
        monitor, 
        nullptr
    );


    if (window_) {
        //  window
        glfwMakeContextCurrent(window_);

        //  ウィンドウリサイズが許可されている場合はコールバック設定
        if (config.window_resizable_) {
            glfwSetWindowSizeCallback(window_, windowResizeCallback);
        }

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


    auto& screen_mgr = t3::ScreenManager::instance();
    Vec2 screen_half = screen_mgr.deviceScreenSize().half();
    data->x_ = (x - screen_half.x_) / screen_half.x_;
    data->y_ = -((y - screen_half.y_) / screen_half.y_);
    
    data->hit_ = (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) != 0);

}

bool isExitRequest() {

    return glfwWindowShouldClose(window_) != 0;
}

CROSS_NS_END

