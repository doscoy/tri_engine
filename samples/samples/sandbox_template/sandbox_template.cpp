

#include "sandbox_template.hpp"



class TemplateScene::SceneContext {

public:
    SceneContext()
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize() {
        glGenFramebuffers(1, &fbo_.id_);
        glGenTextures(1, &tex_);
        glGenRenderbuffers(1, &render_buffer_);
        
        
        // -----------------------------------------------------
        //  テクスチャ初期化

        glBindTexture(GL_TEXTURE_2D, tex_);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            fbo_.width_,
            fbo_.height_,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            0
        );
        
        
        // -----------------------------------------------------
        //  レンダーバッファ初期化
        glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_);
        glRenderbufferStorage(
            GL_RENDERBUFFER,
            GL_DEPTH_COMPONENT,
            fbo_.width_,
            fbo_.height_
        );

        // -----------------------------------------------------
        //  フレームバッファ初期化
        glBindFramebuffer(
            GL_FRAMEBUFFER,
            fbo_.id_
        );

        //  FBOにテクスチャを関連付け
        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,   //  カラーバッファとして設定
            GL_TEXTURE_2D,
            tex_,
            0
        );
        
        glFramebufferRenderbuffer(
            GL_FRAMEBUFFER,
            GL_DEPTH_ATTACHMENT,    //  デブスバッファとして設定
            GL_RENDERBUFFER,
            render_buffer_
        );
    }
    
    void terminate() {
        glDeleteFramebuffers(1, &fbo_.id_);
        glDeleteTextures(1, &tex_);
        glDeleteRenderbuffers(1, &render_buffer_);
    }
    
    void update(t3::tick_t delta_time) {
        
        draw();

    }


    void draw() {
        //  既存のフレームバッファを保存
        GLint default_fbo;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &default_fbo);
    
        //  自分のフレームバッファに変更
        glBindFramebuffer(GL_FRAMEBUFFER, fbo_.id_);
    
        //  フレームバッファを戻す
        glBindFramebuffer(GL_FRAMEBUFFER, default_fbo);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void suspend(t3::tick_t delta_time) {

    }

private:

    struct FrameBuffer {
        FrameBuffer()
            : width_(512)
            , height_(512)
            , id_(0)
        {
        }
        
        
        int width_;
        int height_;
        GLuint id_;
    };

    FrameBuffer fbo_;
    GLuint tex_;
    GLuint render_buffer_;


};






TemplateScene::TemplateScene()
    : Scene( "Template" ) {
    context_.reset(T3_NEW SceneContext());
}

TemplateScene::~TemplateScene() {
    
}


void TemplateScene::initializeScene() {
    context_->initialize();
}


void TemplateScene::terminateScene() {
    context_->terminate();
}


void TemplateScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish(true);
    }
}

void TemplateScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















