

#include "input_test.hpp"



class InputTestScene::SceneContext {

public:
    SceneContext()
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize() {

    }
    
    void terminate() {

    }
    
    void update(t3::tick_t delta_time) {
        
    }


    void suspend(t3::tick_t delta_time) {

    }
    
    void debugRender() {
        const auto& input = t3::Director::instance().input(0);

        //  ポインティングデバイス
        const auto& touch = input.pointing();
        T3_PRINT_DISP(220, 270, "TOUCH DATA");
        T3_PRINT_DISP(220, 280, "TRIGGER : %d", touch.isTrigger());
        T3_PRINT_DISP(220, 290, "HOLD    : %d", touch.isHold());
        T3_PRINT_DISP(220, 300, "RELEASE : %d", touch.isRelease());
        T3_PRINT_DISP(220, 310, "REPEAT  : %d", touch.isRepeat());
        T3_PRINT_DISP(220, 320, "D CLICK : %d", touch.isDoubleClick());
        T3_PRINT_DISP(220, 330, "X : %f", touch.position().x_);
        T3_PRINT_DISP(220, 340, "Y : %f", touch.position().y_);
        

        //  ゲームパッド
        const auto& pad = input.pad();
        T3_PRINT_DISP(10, 110, "PAD DATA TR PR RL RP");
        T3_PRINT_DISP(10, 120, "A     :  %d  %d  %d  %d",
            pad.isTrigger(t3::Pad::BUTTON_A),
            pad.isPress(t3::Pad::BUTTON_A),
            pad.isRelease(t3::Pad::BUTTON_A),
            pad.isRepeat(t3::Pad::BUTTON_A)
        );
        T3_PRINT_DISP(10, 130, "B     :  %d  %d  %d  %d",
            pad.isTrigger(t3::Pad::BUTTON_B),
            pad.isPress(t3::Pad::BUTTON_B),
            pad.isRelease(t3::Pad::BUTTON_B),
            pad.isRepeat(t3::Pad::BUTTON_B)
        );
        T3_PRINT_DISP(10, 140, "X     :  %d  %d  %d  %d",
            pad.isTrigger(t3::Pad::BUTTON_X),
            pad.isPress(t3::Pad::BUTTON_X),
            pad.isRelease(t3::Pad::BUTTON_X),
            pad.isRepeat(t3::Pad::BUTTON_X)
        );

        T3_PRINT_DISP(10, 150, "Y     :  %d  %d  %d  %d",
            pad.isTrigger(t3::Pad::BUTTON_Y),
            pad.isPress(t3::Pad::BUTTON_Y),
            pad.isRelease(t3::Pad::BUTTON_Y),
            pad.isRepeat(t3::Pad::BUTTON_Y)
        );
        
        T3_PRINT_DISP(10, 160, "L     :  %d  %d  %d  %d",
            pad.isTrigger(t3::Pad::BUTTON_L),
            pad.isPress(t3::Pad::BUTTON_L),
            pad.isRelease(t3::Pad::BUTTON_L),
            pad.isRepeat(t3::Pad::BUTTON_L)
        );
        T3_PRINT_DISP(10, 170, "R     :  %d  %d  %d  %d",
            pad.isTrigger(t3::Pad::BUTTON_R),
            pad.isPress(t3::Pad::BUTTON_R),
            pad.isRelease(t3::Pad::BUTTON_R),
            pad.isRepeat(t3::Pad::BUTTON_R)
        );
        T3_PRINT_DISP(10, 180, "UP    :  %d  %d  %d  %d",
            pad.isTrigger(t3::Pad::BUTTON_UP),
            pad.isPress(t3::Pad::BUTTON_UP),
            pad.isRelease(t3::Pad::BUTTON_UP),
            pad.isRepeat(t3::Pad::BUTTON_UP)
        );
        T3_PRINT_DISP(10, 190, "DOWN  :  %d  %d  %d  %d",
            pad.isTrigger(t3::Pad::BUTTON_DOWN),
            pad.isPress(t3::Pad::BUTTON_DOWN),
            pad.isRelease(t3::Pad::BUTTON_DOWN),
            pad.isRepeat(t3::Pad::BUTTON_DOWN)
        );
        T3_PRINT_DISP(10, 200, "RIGHT :  %d  %d  %d  %d",
            pad.isTrigger(t3::Pad::BUTTON_RIGHT),
            pad.isPress(t3::Pad::BUTTON_RIGHT),
            pad.isRelease(t3::Pad::BUTTON_RIGHT),
            pad.isRepeat(t3::Pad::BUTTON_RIGHT)
        );
        T3_PRINT_DISP(10, 210, "LEFT  :  %d  %d  %d  %d",
            pad.isTrigger(t3::Pad::BUTTON_LEFT),
            pad.isPress(t3::Pad::BUTTON_LEFT),
            pad.isRelease(t3::Pad::BUTTON_LEFT),
            pad.isRepeat(t3::Pad::BUTTON_LEFT)
        );
        T3_PRINT_DISP(10, 220, "HOME  :  %d  %d  %d  %d",
            pad.isTrigger(t3::Pad::BUTTON_HOME),
            pad.isPress(t3::Pad::BUTTON_HOME),
            pad.isRelease(t3::Pad::BUTTON_HOME),
            pad.isRepeat(t3::Pad::BUTTON_HOME)
        );
        T3_PRINT_DISP(10, 230, "DEBUG1:  %d  %d  %d  %d",
            pad.isTrigger(t3::Pad::DEBUG_BUTTON_1),
            pad.isPress(t3::Pad::DEBUG_BUTTON_1),
            pad.isRelease(t3::Pad::DEBUG_BUTTON_1),
            pad.isRepeat(t3::Pad::DEBUG_BUTTON_1)
        );
        T3_PRINT_DISP(10, 240, "DEBUG2:  %d  %d  %d  %d",
            pad.isTrigger(t3::Pad::DEBUG_BUTTON_2),
            pad.isPress(t3::Pad::DEBUG_BUTTON_2),
            pad.isRelease(t3::Pad::DEBUG_BUTTON_2),
            pad.isRepeat(t3::Pad::DEBUG_BUTTON_2)
        );

        //  加速度センサ
        const auto& acc = input.accelerometer();
        T3_PRINT_DISP(10, 270, "ACCELEROMETER");
        T3_PRINT_DISP(10, 280, "X %f", acc.x_);
        T3_PRINT_DISP(10, 290, "Y %f", acc.y_);
        T3_PRINT_DISP(10, 300, "Z %f", acc.z_);
        
    }

private:

};






InputTestScene::InputTestScene()
    : Scene( "InputTestScene" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

InputTestScene::~InputTestScene() {
    
}


void InputTestScene::initializeScene() {
    context_->initialize();
}


void InputTestScene::terminateScene() {
    context_->terminate();
}


void InputTestScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void InputTestScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}

void InputTestScene::debugRenderScene() {
    context_->debugRender();
}















