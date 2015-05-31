

#include "simple_mesh3.hpp"




class SimpleMesh3Scene::SceneContext
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
        layer_.name("SimpleMesh3Scene::DrawLayer");
        layer_.setUpdateCallback<SimpleMesh3Scene::SceneContext>(this, &SceneContext::layerUpdate);
        layer_.setRenderCallback<SimpleMesh3Scene::SceneContext>(this, &SceneContext::layerRender);


        //  モデル作成
        t3::FilePath obj_path("character_chr_old.obj");
        model_ = t3::Model::create(obj_path.fullpath().c_str());

        
        //  カメラ位置調整
        float len = model_->mesh()->boundingSphere().radius();
        cam_updater_.position(0, len*2, len*4);
        cam_updater_.targetPosition(0,0,0);
        
        //  シーングラフ初期化
        scene_graph_.camera(cam_updater_.camera());
        node1_ = scene_graph_.createNode();
        node1_->attachEntity(model_.get());
    }
    
    void terminate(){
    
    }
    
    void update(t3::tick_t delta_time){
        static float angle;
        angle += 0.25f;
        node1_->rotationY(angle);
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
    t3::ModelPtr model_;
    t3::LookAtCameraUpdater cam_updater_;
    t3::SceneGraph scene_graph_;
    
    t3::TransformNodePtr node1_;
};






SimpleMesh3Scene::SimpleMesh3Scene()
    : Scene( "MeshObjScene" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

SimpleMesh3Scene::~SimpleMesh3Scene() {
    
}


void SimpleMesh3Scene::initializeScene() {
    context_->initialize();
}


void SimpleMesh3Scene::terminateScene() {
    context_->terminate();
}


void SimpleMesh3Scene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    auto& gs = t3::Director::instance();
    auto& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void SimpleMesh3Scene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}















