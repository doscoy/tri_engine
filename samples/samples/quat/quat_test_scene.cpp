

#include "quat_test_scene.hpp"




class QuatTestScene::SceneContext
{
public:
    SceneContext()
        : layer_()
        , model_()
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize() {
        layer_.setRenderCallback<QuatTestScene::SceneContext>(this, &SceneContext::layerRender);

        //  メッシュ読み込み
        t3::FilePath obj_path("ninja.obj");
    

        //  モデル作成
        model_ = t3::Model::create(obj_path);

        
        //  カメラ生成
        const auto& sphere = model_->mesh()->boundingSphere();
        cam_update_.position(sphere.position() + t3::Vec3(0, 0, sphere.radius() * 2));
        cam_update_.targetPosition(sphere.position());
    }
    
    void terminate() {

    }
    
    void update(t3::tick_t delta_time){

        auto& pt = t3::Director::input().pointing();

        if (pt.isHold()) {
        
            t3::Quaternion move;
            
            if (pt.position().x_ > 0) {
                move.set(t3::Vec3::axisX(), 1);
            }
            else {
                move.set(t3::Vec3::axisY(), 1);
            }
            
            quat_.rotate(move);
            
        }
    }

    void suspend(t3::tick_t delta_time) {
    
    }
    
    
private:
    
    void layerRender() {

        t3::RenderSystem::setCulling(false);
        t3::RenderSystem::setCullingMode(t3::RenderSystem::CullingMode::MODE_BACK);
        t3::RenderSystem::setBlend(false);
        t3::RenderSystem::setDepthTest(true);
        t3::RenderSystem::setDepthWrite(true);
        t3::RenderSystem::setDepthTestMode(t3::RenderSystem::DepthTestMode::MODE_LESS);

        auto& d = t3::Director::instance();
        auto& screen = d.virtualScreenSize();
    
        t3::RenderSystem::setViewport(0, 0, screen.x_, screen.y_);
        t3::Mtx44 projection;
        projection.perspective(60, screen.x_, screen.y_, 0.1f, 100.0f);
    
        const t3::Mtx44& view_mtx = cam_update_.camera()->viewMatrix();

        t3::Mtx44 transform;
        
        t3::Mtx44 rot, scale;
        rot.rotate(quat_);
        scale.scale(1);
        transform = rot * scale;
        
        t3::Mtx44 mtx = transform * view_mtx * projection;
        
//        model_->render(mtx);

    }


private:
    t3::DrawLayer layer_;
    t3::ModelPtr model_;
    t3::LookAtCameraUpdater cam_update_;
    
    t3::Quaternion quat_;
};






QuatTestScene::QuatTestScene()
    : SceneBase( "QuatTestScene" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

QuatTestScene::~QuatTestScene() {
    
}


void QuatTestScene::initializeScene() {
    context_->initialize();
}


void QuatTestScene::terminateScene() {
    context_->terminate();
}


void QuatTestScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    auto& gs = t3::Director::instance();
    auto& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void QuatTestScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















