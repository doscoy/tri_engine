////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#ifndef COLLADA_MESH2_HPP_INCLUDED
#define COLLADA_MESH2_HPP_INCLUDED


#include "tri_engine.hpp"



class ColladaMesh2Scene
    : public t3::jet::Scene3D
{
public:
    ColladaMesh2Scene();
    ~ColladaMesh2Scene();
    
public:
    void initialize() override;
    void terminate() override;
    void update(const t3::FrameInfo& frame_info) override;
    
private:
    t3::DrawLayerPtr final_layer_;
    t3::CinemaLayerPtr cinema_;
    t3::RotateCameraUpdaterPtr cam_updater_;
    t3::SceneGraph scene_graph_;
    t3::TransformNodePtr node_cone_;
    t3::TransformNodePtr node_object3_;
    t3::CameraTouchControllerPtr cam_controller_;
};

#endif // SIMPLE_MESH2_HPP_INCLUDED
