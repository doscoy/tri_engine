#include "kernel/memory/tri_new.hpp"
#include "gfx/tri_projector.hpp"
#include "math/tri_math_util.hpp"



namespace t3 {



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

    ProjectorPtr projctor(T3_SYS_NEW Projector(Vec2(256,256), 45.0f, 1.0f, 1000.0f));
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

}   // namespace nd

