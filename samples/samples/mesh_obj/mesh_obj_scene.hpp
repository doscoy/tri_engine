
#ifndef MESH_OBJ_TEST_HPP_INCLUDED
#define MESH_OBJ_TEST_HPP_INCLUDED


#include "tri_engine.hpp"


class MeshObjScene
    : public t3::Scene
{
public:
    MeshObjScene();
    ~MeshObjScene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(t3::tick_t delta_time) override;
    void suspendScene(t3::tick_t delta_time) override;
private:
    class SceneContext;
    t3::ScopedPtr<SceneContext> context_;

};

#endif // MESH_OBJ_TEST_HPP_INCLUDED
