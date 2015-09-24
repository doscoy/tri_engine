
#ifndef COLLADA_MESH2_HPP_INCLUDED
#define COLLADA_MESH2_HPP_INCLUDED


#include "tri_engine.hpp"



class ColladaMesh2Scene
    : public t3::jet::Scene
{
public:
    ColladaMesh2Scene();
    ~ColladaMesh2Scene();
    
public:
    void initialize() override;
    void terminate() override;
    void update() override;
    
private:
    t3::DrawLayer final_layer_;
    t3::CinemaLayer cinema_;
    t3::RotateCameraUpdater cam_updater_;
    t3::LookAtCameraUpdater light_camera_;
    t3::SceneGraph scene_graph_;
    t3::TransformNodePtr node_cone_;


};
#endif // SIMPLE_MESH2_HPP_INCLUDED
