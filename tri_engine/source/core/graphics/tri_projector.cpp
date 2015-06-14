#include "core/kernel/memory/tri_new.hpp"
#include "core/graphics/tri_projector.hpp"
#include "core/math/tri_math_util.hpp"
#include "core/base/tri_director.hpp"

TRI_CORE_NS_BEGIN




Projector::Projector(
    const Vec2& screen,
    float fov,
    float near,
    float far  
)   : mtx_()
    , screen_size_(screen)
    , calc_request_(true)
    , fov_(fov)
    , near_(near)
    , far_(far)
{}


Projector::~Projector()
{}

ProjectorPtr Projector::create() {
    auto& d = Director::instance();
    ProjectorPtr projctor(T3_SYS_NEW Projector(d.deviceScreenSize(), 45.0f, 1.0f, 1000.0f));
    return projctor;
}

ProjectorPtr Projector::create(
    const Vec2& screen,
    float fov,
    float near,
    float far
) {

    ProjectorPtr projctor(T3_SYS_NEW Projector(screen, fov, near, far));
    return projctor;
}


void Projector::recalcurate() {
    mtx_.perspective(fov_, screen_size_.x_, screen_size_.y_, near_, far_);
}

TRI_CORE_NS_END

