/**
    @file tri_projector.hpp
    色情報.
*/
#ifndef TRI_PROJECTOR_HPP_INCLUDED
#define TRI_PROJECTOR_HPP_INCLUDED

//  include
#include "base/tri_std.hpp"
#include "math/tri_matrix.hpp"

namespace t3 {
class Projector;
using ProjectorPtr = SharedPtr<Projector>;

class Projector {

private:
    Projector(
        const Vec2& screen,
        float fov,
        float near,
        float far  
    );
    
public:
    ~Projector();

public:

    void screenSize(const Vec2& v) {
        screen_size_ = v;
    }

    const Vec2& screenSize() const {
        return screen_size_;
    }

    void near(float n) {
        near_ = n;
    }

    float near() const {
        return near_;
    }

    void far(float f) {
        far_ = f;
    }

    float far() const {
        return far_;
    }

    void fieldOfView(float fov) {
        fov_ = fov;
    }

    float fieldOfView() const {
        return fov_;
    }

    const Mtx44& projectionMatrix() {
        if (calc_request_) {
            recalcurate();
            calc_request_ = false;
        }
        return mtx_;
    }


    static ProjectorPtr create();
    static ProjectorPtr create(
        const Vec2& screen,
        float fov,
        float near,
        float far  
    );
private:
    void recalcurate();

private:
    Mtx44 mtx_;
    Vec2 screen_size_;
    bool calc_request_;
    float fov_;
    float near_;
    float far_;

};


}   // namespace t3



#endif // TRI_PROJECTOR_HPP_INCLUDED

