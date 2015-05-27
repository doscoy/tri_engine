

#include "simple_mesh.hpp"




class SimpleMeshScene::SceneContext
{
public:
    SceneContext()
        : layer_()
        , model_()
        , mesh_(nullptr)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize(){
        layer_.setUpdateCallback<SimpleMeshScene::SceneContext>(this, &SceneContext::layerUpdate);
        layer_.setRenderCallback<SimpleMeshScene::SceneContext>(this, &SceneContext::layerRender);

        //  メッシュ読み込み
        t3::FilePath obj_path("o.obj");
        mesh_ = T3_SYS_NEW t3::Mesh(obj_path.fullpath().c_str());

        //  モデル作成
        model_.mesh(mesh_);

        
        //  カメラ生成
        float len = mesh_->boundingSphere().radius();
        cam_update_.camera(t3::Camera::create());
        cam_update_.position(0, len, len);
        cam_update_.targetPosition(0,0,0);
        
        //  シーングラフ初期化
        scene_graph_.camera(cam_update_.camera());
        node1_ = scene_graph_.createNode();
        node1_->attachEntity(&model_);
    }
    
    void terminate(){
    
    }
    
    void update(t3::tick_t delta_time){
        
    }

    void suspend(t3::tick_t delta_time) {
    
    }
    
private:
    void layerUpdate() {
        scene_graph_.updateScene(t3::frameSec<60>());
    }
    void layerRender() {
        scene_graph_.renderScene();
    }


private:
    t3::DrawLayer layer_;
    t3::Model model_;
    t3::Mesh* mesh_;
    t3::LookAtCameraUpdater cam_update_;
    t3::SceneGraph scene_graph_;
    
    t3::TransformNodePtr node1_;
};






SimpleMeshScene::SimpleMeshScene()
    : Scene( "MeshObjScene" ) {
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
















