

#include "collada_mesh2.hpp"

//
//  複数のシェイプを持つcolladaへの対応テスト
//

ColladaMesh2Scene::ColladaMesh2Scene()
    : Scene("ColladaMeshScene") 
{

}

ColladaMesh2Scene::~ColladaMesh2Scene() {

}


void ColladaMesh2Scene::initialize() {

    T3_RENDER_ASSERT();

    //  キャラクタ作成
    node_cone_ = createModel("cone2.dae");
   
    //  カメラ位置調整
    cam_updater_.center(t3::Vec3(0.0f, 0.0f, 0.0f));
    cam_updater_.distance(20.0f);
        
    //  シーングラフにカメラ設定
    sceneGraph().camera(cam_updater_.camera());
    cam_updater_.updateCamera();


    T3_RENDER_ASSERT();
}


void ColladaMesh2Scene::terminate() {

}


void ColladaMesh2Scene::update() {

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






