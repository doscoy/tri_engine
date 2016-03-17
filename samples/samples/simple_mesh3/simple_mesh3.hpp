////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#ifndef SIMPLE_MESH3_HPP_INCLUDED
#define SIMPLE_MESH3_HPP_INCLUDED


#include "tri_engine.hpp"


class SimpleMesh3Scene
    : public t3::SceneBase
{
public:
    SimpleMesh3Scene();
    ~SimpleMesh3Scene();
    
public:
    void initializeScene() override;
    void updateScene(const t3::DeltaTime delta_time) override;

private:
    void layerRender() {
        scene_graph_.renderScene(t3::RenderInfo::NORMAL);
    }
private:
    t3::DrawLayer layer_;
    t3::ModelPtr model_;
    t3::LookAtCameraUpdaterPtr cam_updater_;
    t3::SceneGraph scene_graph_;
    t3::TransformNodePtr node1_;

};

#endif // SIMPLE_MESH_HPP_INCLUDED
