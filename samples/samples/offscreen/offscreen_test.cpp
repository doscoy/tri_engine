////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


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
    
    void update(t3::DeltaTime delta_time) {
        float rot = sprite_->transform()->rotation().z_;
        sprite_->transform()->rotation(t3::Vec3(0,0,rot + 0.1f));
    }

    void debugRender() {
        
        draw();
    }

    void draw() {
        surface_.preRender();
        
        
        t3::RenderSystem::setDepthWrite(true);
        t3::Color clear_color = t3::color_sample::blue();
        t3::RenderSystem::clearColor(
            clear_color.red(),
            clear_color.green(),
            clear_color.blue(),
            clear_color.alpha()
        );
        t3::RenderSystem::clearBuffer(true, true, false);
        t3::RenderSystem::setDepthTest(true);

        
        modelDraw();
      
        
        //  フレームバッファを戻す
        surface_.postRender();

    }
    
    void modelInit() {
        //  メッシュ読み込み
        t3::FilePath obj_path("bunny.obj");

        //  モデル作成
        model_ = t3::Model::create(obj_path);

        
        //  カメラ生成
        const t3::Sphere& sphere = model_->mesh()->boundingSphere();
        cam_update_.position(sphere.position() + t3::Vec3(0, 0, sphere.radius() * 2));
        cam_update_.targetPosition(sphere.position());
    }
    
    void modelDraw() {
        
        
        
        auto& d = t3::Director::instance();
        auto& screen = d.virtualScreenSize();
    
        t3::RenderSystem::setViewport(0, 0, surface_.width(), surface_.height());
        t3::Mtx44 projection;
        projection.perspective(60, screen.x_, screen.y_, 0.01f, 1000.0f);
    
    
        t3::RenderSystem::setBlend(false);
        t3::RenderSystem::setCulling(true);
        t3::RenderSystem::setCullingMode(t3::RenderSystem::CullingMode::MODE_BACK);

        t3::RenderSystem::setDepthTestMode(t3::RenderSystem::DepthTestMode::MODE_LESS);
        
    }

    void spriteInit() {
        
        t3::String tex_path = "stamp.png";
        sprite_ = sprite_layer_.createSprite(tex_path);
        sprite_->texture(surface_.colorTexture());
        sprite_->size(400, 450);
        sprite_->adjustPivotByCenter();
    }
    

private:
    t3::SpriteLayer sprite_layer_;
    t3::SpritePtr sprite_;
    t3::ModelPtr model_;
    t3::LookAtCameraUpdater cam_update_;
    t3::Surface surface_;
};






OffscreenTestScene::OffscreenTestScene()
    : SceneBase( "Offscreen" ) {
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


void OffscreenTestScene::updateScene(t3::DeltaTime delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}


void OffscreenTestScene::debugRenderScene() {
    context_->debugRender();
}














