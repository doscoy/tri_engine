

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
        cam_ = std::make_shared<t3::Camera>();
        cam_update_.setCamera(cam_);
        cam_update_.position(0, 3, 4);
        cam_update_.setTargetPosition(0,0,0);
        
        //  シーングラフ初期化
        scene_graph_.setCamera(cam_);
        node_ = scene_graph_.createNode();
        node_->attachEntity(&model_);
        
        
        
    }
    
    void terminate(){
    
    }
    
    void update(t3::tick_t delta_time){
        static float angle = 0;
        angle += 1;
        node_->rotation(angle, 0, 0);
        
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
    
    std::shared_ptr<t3::TransformNode> node_;
    
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
















