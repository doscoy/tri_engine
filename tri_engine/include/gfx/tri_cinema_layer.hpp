#ifndef TRI_CINEMA_LAYER_HPP_INCLUDED
#define TRI_CINEMA_LAYER_HPP_INCLUDED


#include "tri_render_layer.hpp"
#include "tri_shader.hpp"
#include "tri_texture.hpp"


namespace t3 {
  
class CinemaLayer
    : public RenderLayer {
    
public:
    CinemaLayer();
    CinemaLayer(
        const String& name,
        const int priority
    );
    virtual ~CinemaLayer();


public:
    void useTexture(
        TexturePtr tex
    ) {
        texture_ = tex;
    }
    
    void useDefaultShader() {
        shader_ = default_shader_;
    }
    
    void useCustomShader(ShaderPtr shader) {
        shader_ = shader;
    }
private:
    void updateLayer(tick_t delta_time) override;
    void drawLayer() override;
    

private:
    ShaderPtr shader_;
    ShaderPtr default_shader_;
    TexturePtr texture_;
};
  
  
}   // namespace t3



#endif  // TRI_CINEMA_LAYER_HPP_INCLUDED
