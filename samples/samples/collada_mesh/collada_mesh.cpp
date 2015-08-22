

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
    node_chara_ = createModel("plane.dae");
    t3::ModelPtr chara = std::dynamic_pointer_cast<t3::Model>(node_chara_->entity());


    //  太陽作成
    node_sun_ = createModel("sun.obj");
    node_sun_->position(-12,22,-10);

    //  シーングラフ初期化

    //  カメラ位置調整
    float len = chara->mesh()->boundingSphere().radius();
    if (t3::isZeroFloat(len)) {
        len = 5.0f;
    }
    cam_updater_.position(0, len*4, len*8);
    cam_updater_.targetPosition(0, 0, 0);

        
    //  シーングラフにカメラ設定
    sceneGraph().camera(cam_updater_.camera());


    T3_RENDER_ASSERT();
}


void ColladaMeshScene::terminate() {

}


void ColladaMeshScene::update() {

    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}






