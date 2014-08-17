

#include "mesh_obj_scene.hpp"




class MeshObjScene::SceneContext
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
        layer_.setUpdateCallback(this, &SceneContext::layerUpdate);
        layer_.setRenderCallback(this, &SceneContext::layerRender);

        //  メッシュ読み込み
        t3::FilePath obj_path("o.obj");
        mesh_ = new t3::Mesh(obj_path.getFullPath().c_str());
    

        //  モデル作成
        model_.mesh(mesh_);

        
        //  カメラ生成
        cam_ = t3::Camera::create();
        cam_update_.camera(cam_);
        cam_update_.position(0, 5, 5);
        cam_update_.targetPosition(0,0,0);
        
        //  シーングラフ初期化
        scene_graph_.camera(cam_);
        node1_ = scene_graph_.createNode();
        node1_->attachEntity(&model_);
        
        node2_ = node1_->createNode("node2");
        node2_->attachEntity(&model_);
        node2_->position(3, 0, 0);
        
        
    }
    
    void terminate(){
    
    }
    
    void update(t3::tick_t delta_time){
        static float angle = 0;
        angle += 1;
        node1_->rotation(0, angle, 0);
        node2_->rotation(angle*4, 0, 0);
    }

    void suspend(t3::tick_t delta_time) {
    
    }
    
private:
    void layerUpdate(t3::DrawLayer* const, t3::tick_t dt) {
        scene_graph_.updateScene(dt);
        
    }
    void layerRender(t3::DrawLayer* const) {
    
        

        scene_graph_.renderScene();
    }


private:
    t3::DrawLayer layer_;
    t3::Model model_;
    t3::Mesh* mesh_;
    t3::CameraPtr cam_;
    t3::LookAtCameraUpdater cam_update_;
    t3::SceneGraph scene_graph_;
    
    t3::TransformNodePtr node1_;
    t3::TransformNodePtr node2_;
    t3::Quaternion quat_;
};






MeshObjScene::MeshObjScene()
    : Scene( "MeshObjScene" ) {
    context_.reset(T3_NEW SceneContext());
}

MeshObjScene::~MeshObjScene() {
    
}


void MeshObjScene::initializeScene() {
    context_->initialize();
}


void MeshObjScene::terminateScene() {
    context_->terminate();
}


void MeshObjScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    auto& gs = t3::Director::instance();
    auto& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish(true);
    }
}

void MeshObjScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















