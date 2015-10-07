////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/graphics/tri_camera_touch_controller.hpp"
#include "core/base/tri_director.hpp"
#include "core/graphics/tri_camera_updater_events.hpp"

TRI_CORE_NS_BEGIN

void CameraTouchController::taskUpdate(const DeltaTime dt) {
    auto& gs = t3::Director::instance();
    auto& input = gs.input();
    auto& pointing = input.pointing();
    if (pointing.isHold()) {
        if (pointing.isMoving()) {
        
            auto roll_h = std::make_shared<t3::event::CameraRollH>();
            roll_h->speed(pointing.moveDistance().x_);

            auto roll_v = std::make_shared<t3::event::CameraRollV>();
            roll_v->speed(pointing.moveDistance().y_);
            
            t3::EventManager::queueEvent(roll_h);
            t3::EventManager::queueEvent(roll_v);
        }

    }
 

}

TRI_CORE_NS_END

