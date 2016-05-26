////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "shadow_test.hpp"



ShadowTestScene::ShadowTestScene()
    : Scene3D("ShadowTest")
    , cinema_()
{
}

ShadowTestScene::~ShadowTestScene() {
    
}


void ShadowTestScene::initialize() {
    T3_RENDER_ASSERT();
    cinema_ = t3::CinemaLayer::create(t3::Vec2(0,0), t3::Vec2(1.0f, 0.6f));

    //  キャラクタ作成
    node_chara_ = createModel("character_chr_old.obj");
    t3::ModelPtr chara = std::dynamic_pointer_cast<t3::Model>(node_chara_->entity());
    chara->enableShadowCast();

    //  フィールド作成
    node_field_ = createModel("field.obj");
    t3::ModelPtr field = std::dynamic_pointer_cast<t3::Model>(node_field_->entity());
    field->enalbeShadowReceive();

    //  太陽作成
    node_sun_ = createModel("sun.obj");
    node_sun_->position(-12,22,-10);

    //  シーングラフ初期化

    //  カメラ位置調整
    float len = chara->mesh()->boundingSphere().radius();
    cam_updater_ = createTask<t3::LookAtCameraUpdater>();
    cam_updater_->position(0, len*4, len*8);
    cam_updater_->targetPosition(0,0,0);
        
    //  ライトカメラ
    //  太陽の位置からキャラを見る
    light_camera_ = createTask<t3::LookAtCameraUpdater>();
    light_camera_->position(node_sun_->position());
    light_camera_->targetPosition(node_chara_->position());
        
    //  シーングラフにカメラ設定
    sceneGraph().camera(cam_updater_->camera());
    sceneGraph().shadowCamera(light_camera_->camera());
    
    
    cinema_->setupRenderTargetToUserCustom(shadowSurface());

    T3_RENDER_ASSERT();
}


void ShadowTestScene::terminate() {

}


void ShadowTestScene::update(const t3::FrameInfo& frame_info) {
    static t3::Degree angle;
    angle += 0.25f;
    node_chara_->rotationY(angle);
        
        
    auto pointing = t3::Director::instance().input().pointing();
    if (pointing.isHold()) {
        float move_y = pointing.moveDistance().y_;
        if (std::abs(move_y) > 2) {
            cam_updater_->dollyFront(move_y*0.1f);
        }
    }

    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}






