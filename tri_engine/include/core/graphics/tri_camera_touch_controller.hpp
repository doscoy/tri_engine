////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_camera_updater.hpp
    タッチでカメラ操作.
*/

#ifndef TRI_CAMERA_TOUCH_CONTROLLER_HPP_INCLUDED
#define TRI_CAMERA_TOUCH_CONTROLLER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "../math/tri_math.hpp"
#include "tri_camera.hpp"
#include "core/base/tri_std.hpp"
#include "core/base/tri_task.hpp"

TRI_CORE_NS_BEGIN

class CameraTouchController
    : public Task
{
    void taskUpdate(const tick_t dt);
};

TRI_CORE_NS_END

#endif  // TRI_CAMERA_TOUCH_CONTROLLER_HPP_INCLUDED
