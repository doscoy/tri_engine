
#ifndef SIMPLE_MESH2_HPP_INCLUDED
#define SIMPLE_MESH2_HPP_INCLUDED


#include "tri_engine.hpp"


class SimpleMesh2Scene
    : public t3::Scene
{
public:
    SimpleMesh2Scene();
    ~SimpleMesh2Scene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(t3::tick_t delta_time) override;
    void suspendScene(t3::tick_t delta_time) override;
private:
    class SceneContext;
    t3::ScopedPtr<SceneContext> context_;

};

#endif // SIMPLE_MESH2_HPP_INCLUDED
