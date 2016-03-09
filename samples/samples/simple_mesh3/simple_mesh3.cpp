
////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "simple_mesh3.hpp"




class SimpleMesh3Scene::SceneContext
{
public:
    SceneContext(t3::SceneBase* owner)
        : layer_()
        , model_()
        , owner_(owner)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize(){
        //  レイヤー準備
        layer_.name("SimpleMesh3Scene::DrawLayer");
        layer_.setUpdateCallback(this, &SceneContext::layerUpdate);
        layer_.setRenderCallback(this, &SceneContext::layerRender);


        //  モデル作成
        t3::FilePath obj_path("vox.obj");
        model_ = t3::Model::create(obj_path);

        
        //  カメラ位置調整
        float len = model_->mesh()->boundingSphere().radius();
        cam_updater_ = owner_->createTask<t3::LookAtCameraUpdater>();
        cam_updater_->position(0, len*2, len*4);
        cam_updater_->targetPosition(0,0,0);
        
        //  シーングラフ初期化
        scene_graph_.camera(cam_updater_->camera());
        node1_ = scene_graph_.createNode();
        node1_->entity(model_);
    }
    
    void terminate(){
    
    }
    
    void update(const t3::DeltaTime delta_time){
        static t3::Degree angle;
        angle += 0.25f;
        node1_->rotationY(angle);
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
    t3::LookAtCameraUpdaterPtr cam_updater_;
    t3::SceneGraph scene_graph_;
    t3::TransformNodePtr node1_;
    SceneBase* owner_;
};






SimpleMesh3Scene::SimpleMesh3Scene()
    : SceneBase("MeshObjScene") {
    context_.reset(T3_SYS_NEW SceneContext(this));
}

SimpleMesh3Scene::~SimpleMesh3Scene() {
    
}


void SimpleMesh3Scene::initializeScene() {
    context_->initialize();
}


void SimpleMesh3Scene::terminateScene() {
    context_->terminate();
}


void SimpleMesh3Scene::updateScene(const t3::DeltaTime delta_time) {
    context_->update(delta_time);
    
    auto& gs = t3::Director::instance();
    auto& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}














