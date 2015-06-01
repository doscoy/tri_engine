

#include "shadow_test.hpp"



class ShadowTestScene::SceneContext {

public:
    SceneContext()
        : layer_()
        , cinema_()
        , chara_()
        , field_()
        , surface_(150,150)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize(){
        //  レイヤー準備
        layer_.name("ShadowTestScene::DrawLayer");
        layer_.setUpdateCallback<ShadowTestScene::SceneContext>(this, &SceneContext::layerUpdate);
        layer_.setRenderCallback<ShadowTestScene::SceneContext>(this, &SceneContext::layerRender);


        //  キャラクタ作成
        t3::FilePath char_path("character_chr_old.obj");
        chara_ = t3::Model::create(char_path.fullpath().c_str());

        //  フィールド作成
        t3::FilePath field_path("field.obj");
        field_ = t3::Model::create(field_path.fullpath().c_str());

        //  ライト作成
        t3::FilePath sun_path("sun.obj");
        sun_ = t3::Model::create(sun_path.fullpath().c_str());
        
        //  カメラ位置調整
        float len = chara_->mesh()->boundingSphere().radius();
        cam_updater_.position(0, len*4, len*8);
        cam_updater_.targetPosition(0,0,0);
        
        //  シーングラフ初期化
        scene_graph_.camera(cam_updater_.camera());
        node_field_ = scene_graph_.createNode();
        node_field_->attachEntity(field_.get());
        node_chara_ = node_field_->createNode("3");
        node_chara_->attachEntity(chara_.get());
        node_sun_ = scene_graph_.createNode();
        node_sun_->attachEntity(sun_.get());
        node_sun_->position(10,20,0);


        //  シャドウ用テクスチャ表示用
        layer_.renderTarget(&surface_);
        cinema_.texture(surface_.texture());
    }
    
    void terminate(){
    
    }
    
    void update(t3::tick_t delta_time){
        static float angle;
        angle += 0.25f;
        node_field_->rotationY(angle);
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
    t3::CinemaLayer cinema_;
    t3::ModelPtr chara_;
    t3::ModelPtr field_;
    t3::ModelPtr sun_;
    t3::LookAtCameraUpdater cam_updater_;
    t3::SceneGraph scene_graph_;
    t3::TransformNodePtr node_field_;
    t3::TransformNodePtr node_chara_;
    t3::TransformNodePtr node_sun_;
    t3::Surface surface_;
};






ShadowTestScene::ShadowTestScene()
    : Scene( "ShadowTest" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

ShadowTestScene::~ShadowTestScene() {
    
}


void ShadowTestScene::initializeScene() {
    context_->initialize();
}


void ShadowTestScene::terminateScene() {
    context_->terminate();
}


void ShadowTestScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void ShadowTestScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















