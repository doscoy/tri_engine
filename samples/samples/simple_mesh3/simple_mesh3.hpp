
#ifndef SIMPLE_MESH3_HPP_INCLUDED
#define SIMPLE_MESH3_HPP_INCLUDED


#include "tri_engine.hpp"


class SimpleMesh3Scene
    : public t3::Scene
{
public:
    SimpleMesh3Scene();
    ~SimpleMesh3Scene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(t3::tick_t delta_time) override;
    void suspendScene(t3::tick_t delta_time) override;
private:
    class SceneContext;
    t3::ScopedPtr<SceneContext> context_;

};

#endif // SIMPLE_MESH_HPP_INCLUDED
