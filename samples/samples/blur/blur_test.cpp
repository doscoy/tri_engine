////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "blur_test.hpp"
#include "shader/tri_simple_tex.vsh"


class BlurScene::SceneContext {

public:
    SceneContext()
        : layer_()
        , screen_()
        , sprite_(nullptr)
        , surface_()
        , moz_lv_(0)
    {

    layer_ = t3::SpriteLayer::create();
    layer_->setupRenderTargetToDevice();

    surface_ = t3::ColorDepthSurface::create(512, 512);

    const char* pass1_fsh = R"(
        #version 300 es
        precision mediump float;

        in vec2 v_texture_uv;
        uniform sampler2D sampler;
        uniform float const_f_0;       // texel offset = (1/height)
        uniform float const_fa_0[5];   // weight
        layout (location = 0) out vec4 FragColor;

        void main() {
            vec4 sum = texture(sampler, v_texture_uv) * const_fa_0[0];
            for (int i = 1; i < 5; ++i) {
                sum += texture(sampler, v_texture_uv + vec2(0.0, float(i) * const_f_0)) * const_fa_0[i];
                sum += texture(sampler, v_texture_uv - vec2(0.0, float(i) * const_f_0)) * const_fa_0[i];
            }

            FragColor = sum;
        }
    )";


        shader_ = t3::Shader::create(simple_tex_vsh, pass1_fsh);

    }
    
    ~SceneContext()
    {}
  
public:
    void initialize() {

        screen_ = t3::CinemaLayer::create();


        //  スプライト生成
        sprite_ = layer_->createSprite("piko.png");
        //  スプライトレイヤはオフスクリーンに書く
//        layer_.setupRenderTargetToUserCustom(&surface_);
        
//        screen_.texture(surface_.colorTexture());
//        screen_.shader(shader_);
        
        pola_.startInterpolation(moz_lv_, 13, 33.0f, t3::InterpolationType::LINER);
    }
    
    void terminate() {

    }
    

    void update(const t3::FrameInfo& frame_info) {
        sprite_->transform()->rotateZ(t3::Degree(0.33f * frame_info.deltaRate()));
        
        pola_.updateInterpolation(frame_info);
        shader_->setConstFloat(0, static_cast<float>(moz_lv_));
    }

private:
    t3::SpriteLayerPtr layer_;
    t3::CinemaLayerPtr screen_;
    t3::SpritePtr sprite_;
    t3::SurfacePtr surface_;
    t3::ShaderPtr shader_;
    t3::Interpolation<int> pola_;
    int moz_lv_;
};






BlurScene::BlurScene()
    : SceneBase( "Blur" ) {
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


void BlurScene::updateScene(const t3::FrameInfo& frame_info) {
    context_->update(frame_info);
    
    auto& gs = t3::Director::instance();
    auto& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

















