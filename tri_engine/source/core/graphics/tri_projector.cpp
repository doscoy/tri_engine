////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

//  include
#include "core/kernel/memory/tri_new.hpp"
#include "core/graphics/tri_projector.hpp"
#include "core/math/tri_math_util.hpp"
#include "core/base/tri_screen_manager.hpp"

TRI_CORE_NS_BEGIN



///
/// コンストラクタ
Projector::Projector(
    const Vec2& screen,
    Degree fov,
    float near,
    float far  
)   : mtx_()
    , screen_size_(screen)
    , calc_request_(true)
    , fov_(fov)
    , near_(near)
    , far_(far)
{}

///
/// デストラクタ
Projector::~Projector()
{}

///
/// 生成
ProjectorPtr Projector::create() {
    auto& screen_mgr = ScreenManager::instance();
    ProjectorPtr projctor(T3_SYS_NEW Projector(
        screen_mgr.virtualScreenSize(),
        45.0f,
        1.0f,
        1000.0f
    ));
    return projctor;
}

///
/// 生成
ProjectorPtr Projector::create(
    const Vec2& screen,
    Degree fov,
    float near,
    float far
) {

    ProjectorPtr projctor(T3_SYS_NEW Projector(screen, fov, near, far));
    return projctor;
}

///
/// 行列再計算
void Projector::recalcurate() {
    mtx_.perspective(toRadian(fov_), screen_size_.x_, screen_size_.y_, near_, far_);
}

TRI_CORE_NS_END

