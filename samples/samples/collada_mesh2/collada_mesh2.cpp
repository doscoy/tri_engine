////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "collada_mesh2.hpp"

//
//  複数のシェイプを持つcolladaへの対応テスト
//

ColladaMesh2Scene::ColladaMesh2Scene()
    : t3::jet::Scene("ColladaMesh2Scene") 
    , final_layer_()
    , cinema_()
    , cam_updater_()
    , scene_graph_()
    , node_cone_()
    , node_object3_()
    , cam_controller_()
{
}

ColladaMesh2Scene::~ColladaMesh2Scene() {

}


void ColladaMesh2Scene::initialize() {

    T3_RENDER_ASSERT();

    //  キャラクタ作成
    node_cone_ = createModel("cone2.dae");
    node_object3_ = createModel("object3.dae");
    node_object3_->position(3, 0, 2);
    
    //  カメラ位置調整
    cam_updater_ = createTask<t3::RotateCameraUpdater>();
    cam_updater_->center(t3::Vec3(0.0f, 0.0f, 0.0f));
    cam_updater_->distance(20.0f);

        
    //  シーングラフにカメラ設定
    sceneGraph().camera(cam_updater_->camera());

    cam_controller_ = createTask<t3::CameraTouchController>();


    T3_RENDER_ASSERT();
}


void ColladaMesh2Scene::terminate() {

}


void ColladaMesh2Scene::update(const t3::DeltaTime dt) {

    auto& gs = t3::Director::instance();
    auto& input = gs.input();
    const t3::Pad& pad = input.pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}






