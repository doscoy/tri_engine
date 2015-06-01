
#ifndef SHADOW_TEST_HPP_INCLUDED
#define SHADOW_TEST_HPP_INCLUDED


#include "tri_engine.hpp"


class ShadowTestScene
    : public t3::Scene
{
public:
    ShadowTestScene();
    ~ShadowTestScene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(t3::tick_t delta_time) override;
    void suspendScene(t3::tick_t delta_time) override;
    
private:
    class SceneContext;
    t3::ScopedPtr<SceneContext> context_;

};

#endif // SANDBOX_TEMPLATE_HPP_INCLUDED
