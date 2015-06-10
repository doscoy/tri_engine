

#include "offscreen_test.hpp"



class OffscreenTestScene::SceneContext {

public:
    SceneContext()
        : surface_(t3::Director::screenSize().x_, t3::Director::screenSize().y_, t3::Surface::Type::COLOR_DEPTH)
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
        surface_.preRender();
        
        
        cross::RenderSystem::setDepthWrite(true);
        t3::Color clear_color = t3::color_sample::blue();
        cross::RenderSystem::clearColor(
            clear_color.red(),
            clear_color.green(),
            clear_color.blue(),
            clear_color.alpha()
        );
        cross::RenderSystem::clearBuffer(true, true, false);
        cross::RenderSystem::setDepthTest(true);

        
        modelDraw();
      
        
        //  フレームバッファを戻す
        surface_.postRender();

    }
    
    void modelInit() {
        //  メッシュ読み込み
        t3::FilePath obj_path("bunny.obj");

        //  モデル作成
        model_ = t3::Model::create(obj_path.fullpath().c_str());

        
        //  カメラ生成
        const t3::Sphere& sphere = model_->mesh()->boundingSphere();
        cam_update_.position(sphere.position() + t3::Vec3(0, 0, sphere.radius() * 2));
        cam_update_.targetPosition(sphere.position());
    }
    
    void modelDraw() {
        
        
        
        auto& d = t3::Director::instance();
        auto& screen = d.virtualScreenSize();
    
        cross::RenderSystem::setViewport(0, 0, surface_.width(), surface_.height());
        t3::Mtx44 projection;
        projection.perspective(60, screen.x_, screen.y_, 0.01f, 1000.0f);
    
        const auto view_mtx = cam_update_.camera()->viewMatrix();


        static int rotY;
        rotY++;
        t3::Mtx44 transform = t3::Mtx44::getRotateY(rotY);
        
        
        t3::Mtx44 mtx = transform * view_mtx * projection;

        cross::RenderSystem::setBlend(false);
        cross::RenderSystem::setCulling(true);
        cross::RenderSystem::setCullingMode(cross::RenderSystem::CullingMode::MODE_BACK);

        cross::RenderSystem::setDepthTestMode(cross::RenderSystem::DepthTestMode::MODE_LESS);
//        model_->render(mtx);
    }

    void spriteInit() {
        
        t3::String tex_path = "stamp.png";
        sprite_ = sprite_layer_.createSprite(tex_path);
        sprite_->texture(surface_.colorTexture());
        sprite_->size(400, 450);
        sprite_->adjustPivotByCenter();
    }
    

    void suspend(t3::tick_t delta_time) {

    }

private:
    t3::SpriteLayer sprite_layer_;
    t3::SpritePtr sprite_;
    t3::ModelPtr model_;
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














