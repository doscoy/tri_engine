
#ifndef BLUR_TEST_HPP_INCLUDED
#define BLUR_TEST_HPP_INCLUDED


#include "tri_engine.hpp"


class BlurScene
    : public t3::Scene
{
public:
    BlurScene();
    ~BlurScene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(t3::tick_t delta_time) override;
    void suspendScene(t3::tick_t delta_time) override;
    
private:
    class SceneContext;
    t3::ScopedPtr<SceneContext> context_;

};

#endif // BLUR_TEST_HPP_INCLUDED
