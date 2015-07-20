

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
        model_ = t3::Model::create(obj_path.fullpath().c_str());

        
        //  カメラ位置調整
        float len = model_->mesh()->boundingSphere().radius();
        cam_updater_.position(0, 10, 10);
        cam_updater_.targetPosition(0,0,0);
        
        //  シーングラフ初期化
        scene_graph_.camera(cam_updater_.camera());
        node1_ = scene_graph_.createNode();
        node1_->entity(model_);
    }
    
    void terminate(){
    
    }
    
    void update(t3::tick_t delta_time){
        
    }

    void suspend(t3::tick_t delta_time) {
    
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


void SimpleMeshScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    auto& gs = t3::Director::instance();
    auto& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void SimpleMeshScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















