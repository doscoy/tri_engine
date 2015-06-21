
#ifndef QUAT_TEST_HPP_INCLUDED
#define QUAT_TEST_HPP_INCLUDED


#include "tri_engine.hpp"


class QuatTestScene
    : public t3::SceneBase
{
public:
    QuatTestScene();
    ~QuatTestScene();
    
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
