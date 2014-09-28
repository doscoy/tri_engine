
#ifndef MEM_POOL_TEST_HPP_INCLUDED
#define MEM_POOL_TEST_HPP_INCLUDED


#include "tri_engine.hpp"


class MemPoolScene
    : public t3::Scene
{
public:
    MemPoolScene();
    ~MemPoolScene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(t3::tick_t delta_time) override;
    void suspendScene(t3::tick_t delta_time) override;
    void debugRenderScene() override;
    

private:
    class SceneContext;
    t3::ScopedPtr<SceneContext> context_;

};

#endif // SANDBOX_TEMPLATE_HPP_INCLUDED
