

#include "simple_mesh2.hpp"




class SimpleMesh2Scene::SceneContext
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
        layer_.setUpdateCallback<SimpleMesh2Scene::SceneContext>(this, &SceneContext::layerUpdate);
        layer_.setRenderCallback<SimpleMesh2Scene::SceneContext>(this, &SceneContext::layerRender);

        //  メッシュ読み込み
        t3::FilePath donut_path("poly.obj");
        t3::FilePath bunny_path("bunny.obj");
    
        //  モデル作成
        model_ = t3::Model::create(bunny_path.fullpath().c_str());
        float model_radius = model_->mesh()->boundingSphere().radius();


        //  カメラ生成
        cam_update_.position(0, model_radius * 5, model_radius * 5);
        cam_update_.targetPosition(0,0,0);
        
        //  シーングラフ初期化
        scene_graph_.camera(cam_update_.camera());
        node1_ = scene_graph_.createNode();
        node1_->attachEntity(model_.get());
        node2_ = node1_->createNode("node2");
        node2_->attachEntity(model_.get());
        node2_->position(model_radius * 2, 0, 0);
        
        
    }
    
    void terminate(){
    
    }
    
    void update(t3::tick_t delta_time){
        static float angle = 0;
        angle += 1;
        node1_->rotationY(angle);
        node2_->rotation(angle, 0, 0);
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
    t3::LookAtCameraUpdater cam_update_;
    t3::SceneGraph scene_graph_;
    
    t3::TransformNodePtr node1_;
    t3::TransformNodePtr node2_;
};






SimpleMesh2Scene::SimpleMesh2Scene()
    : SceneBase( "MeshObjScene" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

SimpleMesh2Scene::~SimpleMesh2Scene() {
    
}


void SimpleMesh2Scene::initializeScene() {
    context_->initialize();
}


void SimpleMesh2Scene::terminateScene() {
    context_->terminate();
}


void SimpleMesh2Scene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    auto& gs = t3::Director::instance();
    auto& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void SimpleMesh2Scene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















