
#ifndef OFFSCREEN_HPP_INCLUDED
#define OFFSCREEN_HPP_INCLUDED


#include "tri_engine.hpp"


class OffscreenTestScene
    : public t3::Scene
{
public:
    OffscreenTestScene();
    ~OffscreenTestScene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(t3::tick_t delta_time) override;
    void suspendScene(t3::tick_t delta_time) override;
    
private:
    class SceneContext;
    std::unique_ptr<SceneContext> context_;

};

#endif // SANDBOX_TEMPLATE_HPP_INCLUDED
