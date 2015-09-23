

#include "collada_mesh.hpp"




ColladaMeshScene::ColladaMeshScene()
    : Scene("ColladaMeshScene") 
{

}

ColladaMeshScene::~ColladaMeshScene() {

}


void ColladaMeshScene::initialize() {

    T3_RENDER_ASSERT();

    //  キャラクタ作成
    node_chara_ = createModel("blue_box.dae");
//    node_chara_ = createModel("character_chr_old.obj");
    node_chara_->scale(3.0f);

    //  太陽作成
    node_sun_ = createModel("sun.obj");
    node_sun_->position(-12,22,-10);

    //  シーングラフ初期化

    //  カメラ位置調整
    float len = 8.0f;//chara->mesh()->boundingSphere().radius();
    if (t3::isZeroFloat(len)) {
        len = 5.0f;
    }

    cam_updater_.center(node_chara_->position());

        
    //  シーングラフにカメラ設定
    sceneGraph().camera(cam_updater_.camera());


    T3_RENDER_ASSERT();
}


void ColladaMeshScene::terminate() {

}


void ColladaMeshScene::update() {

    auto& gs = t3::Director::instance();
    auto& input = gs.input();
    const t3::Pad& pad = input.pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }

    auto& pointing = input.pointing();
    if (pointing.isHold()) {
        if (pointing.isMoving()) {

            cam_updater_.rotateH(pointing.moveDistance().x_);
            cam_updater_.rotateV(pointing.moveDistance().y_);
            cam_updater_.updateCamera();
        }

    }
 

}






