
#ifndef INPUT_TEST_HPP_INCLUDED
#define INPUT_TEST_HPP_INCLUDED


#include "tri_engine.hpp"


class InputTestScene
    : public t3::SceneBase
{
public:
    InputTestScene();
    ~InputTestScene();
    
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

#endif // INPUT_TEST_HPP_INCLUDED
