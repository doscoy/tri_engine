
#ifndef SHADOW_TEST_HPP_INCLUDED
#define SHADOW_TEST_HPP_INCLUDED


#include "tri_engine.hpp"


class ShadowTestScene
    : public t3::jet::Scene
{
public:
    ShadowTestScene();
    ~ShadowTestScene();
    
public:
    void initialize() override;
    void terminate() override;
    void update() override;
    
private:
    t3::DrawLayer shadow_render_layer_;
    t3::DrawLayer final_layer_;
    t3::CinemaLayer cinema_;
    t3::LookAtCameraUpdater cam_updater_;
    t3::LookAtCameraUpdater light_camera_;
    t3::SceneGraph scene_graph_;
    t3::TransformNodePtr node_field_;
    t3::TransformNodePtr node_chara_;
    t3::TransformNodePtr node_sun_;


};

#endif // SANDBOX_TEMPLATE_HPP_INCLUDED
