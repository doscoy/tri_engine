////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "simple_mesh.hpp"


class SimpleMeshScene::SceneContext
{
public:
    SceneContext()
        : layer_()
        , model_()
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize(){
        //  レイヤー準備
        layer_.name("SimpleMeshScene::DrawLayer");
        layer_.setUpdateCallback(this, &SceneContext::layerUpdate);
        layer_.setRenderCallback(this, &SceneContext::layerRender);


        //  モデル作成
        t3::FilePath obj_path("o.obj");
        model_ = t3::Model::create(obj_path);

        
        //  カメラ位置調整
        cam_updater_.position(0, 10, 10);
        cam_updater_.targetPosition(0,0,0);
        
        //  シーングラフ初期化
        scene_graph_.camera(cam_updater_.camera());
        node1_ = scene_graph_.createNode();
        node1_->entity(model_);
    }
    
    void terminate(){
    
    }
    
    void update(const t3::FrameInfo& frame_info){
        
    }
    
private:
    void layerUpdate() {
    }
    void layerRender() {
        scene_graph_.renderScene(t3::RenderInfo::NORMAL);
    }


private:
    t3::DrawLayer layer_;
    t3::ModelPtr model_;
    t3::LookAtCameraUpdater cam_updater_;
    t3::SceneGraph scene_graph_;
    
    t3::TransformNodePtr node1_;
};






SimpleMeshScene::SimpleMeshScene()
    : SceneBase( "MeshObjScene" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

SimpleMeshScene::~SimpleMeshScene() {
    
}


void SimpleMeshScene::initializeScene() {
    context_->initialize();
}


void SimpleMeshScene::terminateScene() {
    context_->terminate();
}


void SimpleMeshScene::updateScene(const t3::FrameInfo& frame_info) {
    context_->update(frame_info);
    
    auto& gs = t3::Director::instance();
    auto& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}


















