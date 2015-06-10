//
//  tri_render_info.hpp
//  tri_engine
//
//  Created by KANI Tetsuro on 2015/06/09.
//  Copyright (c) 2015年 KANI Tetsuro. All rights reserved.
//

#ifndef tri_engine_tri_render_info_hpp
#define tri_engine_tri_render_info_hpp

#include "math/tri_matrix.hpp"
#include "gfx/tri_texture.hpp"
namespace t3 {
class RenderInfo {
public:
    const Mtx44* transform() const {
        return transform_;
    }
    
    void transform(const Mtx44* m) {
        transform_ = m;
    }
    
    const Mtx44& projMatrix() const {
        return projection_mtx_;
    }

    void projMatrix(const Mtx44& m) {
        projection_mtx_ = m;
    }
    
    
    const Mtx44& lightMatrix() const {
        return *light_mtx_;
    }

    void lightMatrix(const Mtx44* m) {
        light_mtx_ = m;
    }
    
    const TexturePtr shadowTexture() const {
        return shadow_texture_;
    }
    
    void shadowTexture(TexturePtr tex) {
        shadow_texture_ = tex;
    }
    
    enum Mode {
        SHADOW,
        NORMAL
    };
    
    void renderMode(Mode mode) {
        mode_ = mode;
    }
    
    Mode renderMode() const {
        return mode_;
    }

private:
    const Mtx44* transform_;
    const Mtx44* light_mtx_;
    Mtx44 projection_;
    TexturePtr shadow_texture_;
    Mode mode_;
};
}   // namespace t3;



#endif
