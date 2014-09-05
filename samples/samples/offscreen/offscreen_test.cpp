

#include "offscreen_test.hpp"



class OffscreenTestScene::SceneContext {

public:
    SceneContext()
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize() {
        const t3::Vec2& screen = t3::Director::screenSize();
        offtex_ = t3::Texture::create(
            "offscreentex",
            screen.x_,
            screen.y_,
            t3::RenderSystem::ColorFormat::RGBA
        );
    
        GLint default_fbo;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &default_fbo);

        glGenFramebuffers(1, &surface_.fb_);
        glGenRenderbuffers(1, &surface_.rb_);
            T3_ASSERT(glGetError() == GL_NO_ERROR);

        
        // -----------------------------------------------------
        //  テクスチャ初期化
        glBindTexture(GL_TEXTURE_2D, offtex_->id());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            T3_ASSERT(glGetError() == GL_NO_ERROR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            surface_.width_,
            surface_.height_,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            0
        );
        
            T3_ASSERT(glGetError() == GL_NO_ERROR);

        // -----------------------------------------------------
        //  レンダーバッファ初期化
        glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_);
            T3_ASSERT(glGetError() == GL_NO_ERROR);

        glRenderbufferStorage(
            GL_RENDERBUFFER,
            GL_DEPTH_COMPONENT16,
            surface_.width_,
            surface_.height_
        );

        // -----------------------------------------------------
        //  フレームバッファ初期化
            T3_ASSERT(glGetError() == GL_NO_ERROR);

        glBindFramebuffer(
            GL_FRAMEBUFFER,
            surface_.fb_
        );

        //  FBOにテクスチャを関連付け
        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,   //  カラーバッファとして設定
            GL_TEXTURE_2D,
            offtex_->id(),
            0
        );
        
        glFramebufferRenderbuffer(
            GL_FRAMEBUFFER,
            GL_DEPTH_ATTACHMENT,    //  デブスバッファとして設定
            GL_RENDERBUFFER,
            render_buffer_
        );
        T3_ASSERT(glGetError() == GL_NO_ERROR);


      
//        glBindFramebuffer(GL_FRAMEBUFFER, default_fbo);
//        glBindRenderbuffer(GL_RENDERBUFFER, 0);
//        glBindTexture(GL_TEXTURE_2D, 0);
        
        modelInit();
        spriteInit();
    }
    
    void terminate() {
        glDeleteFramebuffers(1, &surface_.fb_);
        glDeleteRenderbuffers(1, &surface_.rb_);
    }
    
    void update(t3::tick_t delta_time) {
        float rot = sprite_->transform()->rotation();
        sprite_->transform()->rotation(rot + 0.1f);
    }

    void debugRender() {
        
        draw();
    }

    void draw() {
        //  既存のフレームバッファを保存
        GLint default_fb;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &default_fb);
    
        GLint default_rb;
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &default_rb);
    
        //  自分のフレームバッファに変更
        glBindFramebuffer(GL_FRAMEBUFFER, surface_.fb_);
        glBindRenderbuffer(GL_RENDERBUFFER, surface_.rb_);
        
        t3::RenderSystem::clearColor(t3::Color::white());
        t3::RenderSystem::clearBuffer(true, true, false);

        
        modelDraw();

        
    
        //  フレームバッファを戻す
        glBindFramebuffer(GL_FRAMEBUFFER, default_fb);
        glBindFramebuffer(GL_FRAMEBUFFER, default_rb);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void modelInit() {
        //  メッシュ読み込み
        t3::FilePath obj_path("ninja.obj");
        mesh_ = T3_NEW t3::Mesh(obj_path.getFullPath().c_str());
    

        //  モデル作成
        model_.mesh(mesh_);

        
        //  カメラ生成
        const t3::Sphere* sphere = mesh_->getBoundingSphere();;
        cam_ = t3::Camera::create();
        cam_update_.camera(cam_);
        cam_update_.position(sphere->position() + t3::Vec3(0, 0, sphere->radius() * 2));
        cam_update_.targetPosition(sphere->position());

    }
    
    void modelDraw() {
        
        
        
        auto& d = t3::Director::instance();
        auto& screen = d.virtualScreenSize();
    
        t3::RenderSystem::setViewport(0, 0, surface_.width_, surface_.height_);
        t3::Mtx44 projection;
        projection.perspective(60, screen.x_, screen.y_, 0.1f, 100.0f);
    
        const t3::Mtx44& view_mtx = *cam_->viewMatrix();


        static int rotY;
        rotY++;
        t3::Mtx44 transform = t3::Mtx44::getRotateMatrixY(rotY);
        
        
        t3::Mtx44 mtx = transform * view_mtx * projection;
        
        t3::RenderSystem::setBlend(false);
        t3::RenderSystem::setDepthTest(true);
        t3::RenderSystem::setDepthWrite(true);
        t3::RenderSystem::setCulling(true);
        t3::RenderSystem::setCullingMode(t3::RenderSystem::CullingMode::MODE_BACK);
        
        model_.render(mtx);
    }

    void spriteInit() {
        
        t3::FilePath tex_path = "stamp.png";
        sprite_ = sprite_layer_.createSprite(tex_path);
        sprite_->texture(offtex_);
        sprite_->size(400, 450);
        sprite_->adjustPivotByCenter();
    }
    

    void suspend(t3::tick_t delta_time) {

    }

private:

    struct Surface {
        Surface()
            : width_(512)
            , height_(512)
            , fb_(0)
            , rb_(0)
            , depth_(0)
        {
        }
        
        
        int width_;
        int height_;
        GLuint fb_;
        GLuint rb_;
        GLuint depth_;
    };

    Surface surface_;
    GLuint render_buffer_;

    t3::TexturePtr offtex_;

    t3::SpriteLayer sprite_layer_;
    t3::SpritePtr sprite_;
    t3::Model model_;
    t3::Mesh* mesh_;
    t3::CameraPtr cam_;
    t3::LookAtCameraUpdater cam_update_;
};






OffscreenTestScene::OffscreenTestScene()
    : Scene( "Template" ) {
    context_.reset(T3_NEW SceneContext());
}

OffscreenTestScene::~OffscreenTestScene() {
    
}


void OffscreenTestScene::initializeScene() {
    context_->initialize();
}


void OffscreenTestScene::terminateScene() {
    context_->terminate();
}


void OffscreenTestScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void OffscreenTestScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}

void OffscreenTestScene::debugRenderScene() {
    context_->debugRender();
}














