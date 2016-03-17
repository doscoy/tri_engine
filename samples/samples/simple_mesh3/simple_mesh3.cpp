
////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "simple_mesh3.hpp"





SimpleMesh3Scene::SimpleMesh3Scene()
    : SceneBase("MeshObjScene") {

}

SimpleMesh3Scene::~SimpleMesh3Scene() {
    
}


void SimpleMesh3Scene::initializeScene() {
    //  レイヤー準備
    layer_.name("SimpleMesh3Scene::DrawLayer");
    layer_.setRenderCallback(this, &SimpleMesh3Scene::layerRender);


    //  モデル作成
    t3::FilePath obj_path("vox.obj");
    model_ = t3::Model::create(obj_path);

        
    //  カメラ位置調整
    float len = 0.75;//model_->mesh()->boundingSphere().radius();
    cam_updater_ = createTask<t3::LookAtCameraUpdater>();
    cam_updater_->position(0, len*2, len*4);
    cam_updater_->targetPosition(0,0,0);
        
    //  シーングラフ初期化
    scene_graph_.camera(cam_updater_->camera());
    node1_ = scene_graph_.createNode();
    node1_->entity(model_);

}


void SimpleMesh3Scene::updateScene(const t3::DeltaTime delta_time) {
    static t3::Degree angle;
    angle += 0.0025f;
    node1_->rotationY(angle);

    auto& gs = t3::Director::instance();
    auto& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}














