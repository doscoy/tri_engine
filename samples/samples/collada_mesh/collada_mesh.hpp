////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#ifndef COLLADA_MESH_HPP_INCLUDED
#define COLLADA_MESH_HPP_INCLUDED


#include "tri_engine.hpp"



class ColladaMeshScene
    : public t3::jet::Scene3D
{
public:
    ColladaMeshScene();
    ~ColladaMeshScene();
    
public:
    void initialize() override;
    void terminate() override;
    void update(const t3::FrameInfo&) override;
    
private:
    t3::DrawLayer final_layer_;
    t3::CinemaLayer cinema_;
    t3::RotateCameraUpdaterPtr cam_updater_;
    t3::LookAtCameraUpdaterPtr light_camera_;
    t3::SceneGraph scene_graph_;
    t3::TransformNodePtr node_field_;
    t3::TransformNodePtr node_box_;
    t3::TransformNodePtr node_torus_;
    t3::TransformNodePtr node_earth_;
    t3::CameraTouchControllerPtr cam_controller_;
};

#endif // SIMPLE_MESH_HPP_INCLUDED
