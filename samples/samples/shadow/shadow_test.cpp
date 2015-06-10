

#include "shadow_test.hpp"



class ShadowTestScene::SceneContext {

public:
    SceneContext()
        : shadow_render_layer_()
        , final_layer_()
        , cinema_()
        , chara_()
        , field_()
        , cam_updater_()
        , light_camera_()
        , surface_(256, 256, t3::Surface::Type::COLOR_DEPTH)
        , show_color_(true)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize(){
        //  レイヤー準備
        shadow_render_layer_.name("ShadowTestScene::shadow_render_layer_");
        shadow_render_layer_.setUpdateCallback<ShadowTestScene::SceneContext>(this, &SceneContext::shadowUpdate);
        shadow_render_layer_.setRenderCallback<ShadowTestScene::SceneContext>(this, &SceneContext::shadowRender);

        //  レイヤー準備
        final_layer_.name("ShadowTestScene::final_layer_");
        final_layer_.setUpdateCallback<ShadowTestScene::SceneContext>(this, &SceneContext::colorUpdate);
        final_layer_.setRenderCallback<ShadowTestScene::SceneContext>(this, &SceneContext::colorRender);


        //  キャラクタ作成
        t3::FilePath char_path("character_chr_old.obj");
        chara_ = t3::Model::create(char_path.fullpath().c_str());
        chara_->enableShadowCast();
        
        //  フィールド作成
        t3::FilePath field_path("field.obj");
        field_ = t3::Model::create(field_path.fullpath().c_str());

        //  太陽作成
        t3::FilePath sun_path("sun.obj");
        sun_ = t3::Model::create(sun_path.fullpath().c_str());
        
        //  シーングラフ初期化

        node_field_ = scene_graph_.createNode();
        node_field_->attachEntity(field_.get());

        node_chara_ = node_field_->createNode("1");
        node_chara_->attachEntity(chara_.get());

        node_sun_ = scene_graph_.createNode();
        node_sun_->attachEntity(sun_.get());
        node_sun_->position(12,22,0);


        //  カメラ位置調整
        float len = chara_->mesh()->boundingSphere().radius();
        cam_updater_.position(0, len*4, len*8);
        cam_updater_.targetPosition(0,0,0);
        
        //  ライトカメラ
        //  太陽の位置からキャラを見る
        light_camera_.position(node_sun_->position());
        light_camera_.targetPosition(node_chara_->position());
        
        //  シーングラフにライトカメラの行列設定
        scene_graph_.lightCamera(light_camera_.camera());

        //  シャドウ用テクスチャ表示用
        shadow_render_layer_.renderTarget(&surface_);
        scene_graph_.shadowTexture(surface_.depthTexture());

//        showDepth();
    }
    
    void terminate() {
    
    }
    
    void update(t3::tick_t delta_time) {
        static float angle;
        angle += 0.25f;
        node_field_->rotationY(angle);
        
        
        auto pointing = t3::Director::instance().input().pointing();
        if (pointing.isHold()) {
            float move_y = pointing.moveDistance().y_;
            if (std::abs(move_y) > 2) {
                cam_updater_.dollyZ(move_y*0.1f);
            }
        }

        if (pointing.isRelease()) {
            if (show_color_) {
  //              showDepth();
            } else {
  //              showColor();
            }
        }
    }

    void suspend(t3::tick_t delta_time) {
    
    }
    
    void showColor() {
        cinema_.texture(surface_.colorTexture());
        cinema_.useDefaultColorShader();
        show_color_ = true;
    }
    
    void showDepth() {
        cinema_.texture(surface_.depthTexture());
        cinema_.useDefaultDepthShader();
        show_color_ = false;
    }

    
private:
    void shadowUpdate() {
        scene_graph_.updateScene(t3::frameSec<60>());
    }
    void shadowRender() {
        chara_->cullingMode(cross::RenderSystem::CullingMode::MODE_FRONT);
        scene_graph_.camera(light_camera_.camera());
        scene_graph_.renderMode(t3::RenderInfo::SHADOW);
        scene_graph_.renderScene();
    }

    void colorUpdate() {
//        scene_graph_.updateScene(t3::frameSec<60>());
    }
    void colorRender() {
        chara_->cullingMode(cross::RenderSystem::CullingMode::MODE_BACK);
        scene_graph_.renderMode(t3::RenderInfo::NORMAL);
        scene_graph_.camera(cam_updater_.camera());
        scene_graph_.renderScene();
    }




private:
    t3::DrawLayer shadow_render_layer_;
    t3::DrawLayer final_layer_;
    t3::CinemaLayer cinema_;
    t3::ModelPtr chara_;
    t3::ModelPtr field_;
    t3::ModelPtr sun_;
    t3::LookAtCameraUpdater cam_updater_;
    t3::LookAtCameraUpdater light_camera_;
    t3::SceneGraph scene_graph_;
    t3::TransformNodePtr node_field_;
    t3::TransformNodePtr node_chara_;
    t3::TransformNodePtr node_sun_;
    t3::Surface surface_;
    bool show_color_;
};






ShadowTestScene::ShadowTestScene()
    : Scene( "ShadowTest" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

ShadowTestScene::~ShadowTestScene() {
    
}


void ShadowTestScene::initializeScene() {
    context_->initialize();
}


void ShadowTestScene::terminateScene() {
    context_->terminate();
}


void ShadowTestScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void ShadowTestScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















