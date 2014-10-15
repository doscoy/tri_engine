

#include "blur_test.hpp"
#include "../shader/tri_simple_tex.vsh"


class BlurScene::SceneContext {

public:
    SceneContext()
        : layer_()
        , screen_()
        , sprite_(nullptr)
        , surface_(512, 512)
        , moz_lv_(0)
    {

        
        const char* my_fsh = TRI_INSTANT_SHADER(
            varying lowp vec2 v_texture_uv;
            uniform sampler2D sampler;

            uniform mediump float const_f0;

            void main() {
                mediump float pix =const_f0;
                highp vec2 size = vec2(512.0, 512.0);
                highp vec2 target;
                target.x = float(int((v_texture_uv.x * size.x) / pix) * int(pix));
                target.y = float(int((v_texture_uv.y * size.y) / pix) * int(pix));
                highp vec4 c = texture2D(sampler, (target / size));
                gl_FragColor = c;
            }
        );
        
        shader_ = std::make_shared<t3::Shader>(simple_tex_vsh, my_fsh);

    }
    
    ~SceneContext()
    {}
  
public:
    void initialize() {
        //  スプライト生成
        sprite_ = layer_.createSprite("piko.png");
        
        //  スプライトレイヤはオフスクリーンに書く
        layer_.renderTarget(&surface_);
        
        screen_.useTexture(surface_.texture());
        screen_.useCustomShader(shader_);
        
        pola_.startInterpolation(moz_lv_, 13, 33.0f, t3::InterpolationType::LINER);
    }
    
    void terminate() {

    }
    
    void update(t3::tick_t delta_time) {
        float r = sprite_->transform()->rotation();
        sprite_->transform()->rotation(r + 0.33f);
        
        pola_.updateInterpolation(delta_time);
        shader_->setConstFloat(0, moz_lv_);
    }


    void suspend(t3::tick_t delta_time) {

    }

private:
    t3::SpriteLayer layer_;
    t3::CinemaLayer screen_;
    t3::SpritePtr sprite_;
    t3::Surface surface_;
    t3::ShaderPtr shader_;
    t3::Interpolation<int> pola_;
    int moz_lv_;
};






BlurScene::BlurScene()
    : Scene( "Blur" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

BlurScene::~BlurScene() {
    
}


void BlurScene::initializeScene() {
    context_->initialize();
}


void BlurScene::terminateScene() {
    context_->terminate();
}


void BlurScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void BlurScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















