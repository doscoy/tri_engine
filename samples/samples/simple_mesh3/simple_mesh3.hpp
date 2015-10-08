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
    void terminateScene() override;
    void updateScene(const t3::DeltaTime delta_time) override;

private:
    class SceneContext;
    t3::ScopedPtr<SceneContext> context_;

};

#endif // SIMPLE_MESH_HPP_INCLUDED
