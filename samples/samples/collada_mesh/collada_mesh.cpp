////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "collada_mesh.hpp"




ColladaMeshScene::ColladaMeshScene()
    : Scene3D("ColladaMeshScene") 
    , cam_updater_()
    , light_camera_()
    , scene_graph_()
    , node_field_()
    , node_box_()
    , node_torus_()
    , node_earth_()
    , cam_controller_()
{

}

ColladaMeshScene::~ColladaMeshScene() {

}


void ColladaMeshScene::initialize() {

    T3_RENDER_ASSERT();

    //  キャラクタ作成
    node_box_ = createModel("blue_box.dae");
    node_box_->position(5.0f, 3.0f, 0.0f);

    node_torus_ = createModel("sky_torus.dae");
    
    node_earth_ = createModel("earth.dae");
    node_earth_->position(0.0f, 5.0f, 0.0f);

    //  カメラ位置調整
    cam_updater_ = createTask<t3::RotateCameraUpdater>();
    cam_updater_->center(t3::Vec3(0.0f, 2.0f, 0.0f));
    cam_updater_->distance(20.0f);
        
    //  シーングラフにカメラ設定
    sceneGraph().camera(cam_updater_->camera());


    T3_RENDER_ASSERT();
}


void ColladaMeshScene::terminate() {

}


void ColladaMeshScene::update(
    const t3::FrameInfo& frame_info
) {

    auto& gs = t3::Director::instance();
    auto& input = gs.input();
    const t3::Pad& pad = input.pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    } 

}






