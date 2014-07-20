

#include "mesh_obj_scene.hpp"



class MeshObjScene::SceneContext
{
public:
    SceneContext()
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize(){
        layer_.setUpdateCallback(this, &SceneContext::layerUpdate);
        layer_.setRenderCallback(this, &SceneContext::layerRender);

        //  メッシュ読み込み
        t3::FilePath obj_path("teapot.obj");
        mesh_ = new t3::Mesh(obj_path.getFullPath().c_str());
    }
    
    void terminate(){
    
    }
    
    void update(t3::tick_t delta_time){

        
    }

    void suspend(t3::tick_t delta_time) {
    
    }
    
private:
    void layerUpdate(t3::DrawLayer* const, t3::tick_t dt) {
        T3_TRACE("u\n");

    }
    void layerRender(t3::DrawLayer* const) {
        T3_TRACE("r\n");
    }


private:
    t3::DrawLayer layer_;
    t3::Mesh* mesh_;
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
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        setFinish(true);
    }
}

void MeshObjScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















