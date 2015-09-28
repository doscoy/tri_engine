////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#ifndef tri_engine_tri_render_info_hpp
#define tri_engine_tri_render_info_hpp

#include "core/core_config.hpp"
#include "core/math/tri_matrix.hpp"
#include "core/graphics/tri_texture.hpp"




TRI_CORE_NS_BEGIN


class RenderInfo {
public:
    const auto& transform() const {
        return *transform_;
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
    Mtx44 projection_mtx_;
    TexturePtr shadow_texture_;
    Mode mode_;
};


TRI_CORE_NS_END




#endif
