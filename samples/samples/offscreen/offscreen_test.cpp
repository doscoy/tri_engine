

#include "offscreen_test.hpp"



class OffscreenTestScene::SceneContext {

public:
    SceneContext()
        : surface_(t3::Director::screenSize().x_, t3::Director::screenSize().y_)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize() {
        
        modelInit();
        spriteInit();
    }
    
    void terminate() {
    
    }
    
    void update(t3::tick_t delta_time) {
        float rot = sprite_->transform()->rotation().z_;
        sprite_->transform()->rotation(t3::Vec3(0,0,rot + 0.1f));
    }

    void debugRender() {
        
        draw();
    }

    void draw() {
        surface_.bind();
        
        
        t3::RenderSystem::setDepthWrite(true);
        t3::RenderSystem::clearColor(t3::Color::BLUE);
        t3::RenderSystem::clearBuffer(true, true, false);
        t3::RenderSystem::setDepthTest(true);

        
        modelDraw();
      
        
        //  フレームバッファを戻す
        surface_.unbind();

    }
    
    void modelInit() {
        //  メッシュ読み込み
        t3::FilePath obj_path("bunny.obj");
        mesh_ = T3_SYS_NEW t3::Mesh(obj_path.getFullPath().c_str());
    

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
    
        t3::RenderSystem::setViewport(0, 0, surface_.width(), surface_.height());
        t3::Mtx44 projection;
        projection.perspective(60, screen.x_, screen.y_, 0.01f, 1000.0f);
    
        const t3::Mtx44& view_mtx = *cam_->viewMatrix();


        static int rotY;
        rotY++;
        t3::Mtx44 transform = t3::Mtx44::getRotateMatrixY(rotY);
        
        
        t3::Mtx44 mtx = transform * view_mtx * projection;

        t3::RenderSystem::setBlend(false);
        t3::RenderSystem::setCulling(true);
        t3::RenderSystem::setCullingMode(t3::RenderSystem::CullingMode::MODE_BACK);

        t3::RenderSystem::setDepthTestMode(t3::RenderSystem::DepthTestMode::MODE_LESS);
        model_.render(mtx);
    }

    void spriteInit() {
        
        t3::String tex_path = "stamp.png";
        sprite_ = sprite_layer_.createSprite(tex_path);
        sprite_->texture(surface_.texture());
        sprite_->size(400, 450);
        sprite_->adjustPivotByCenter();
    }
    

    void suspend(t3::tick_t delta_time) {

    }

private:
    t3::SpriteLayer sprite_layer_;
    t3::SpritePtr sprite_;
    t3::Model model_;
    t3::Mesh* mesh_;
    t3::CameraPtr cam_;
    t3::LookAtCameraUpdater cam_update_;
    t3::Surface surface_;
};






OffscreenTestScene::OffscreenTestScene()
    : Scene( "Offscreen" ) {
    context_.reset(T3_SYS_NEW SceneContext());
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














