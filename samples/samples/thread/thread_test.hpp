
#ifndef THREAD_TEST_HPP_INCLUDED
#define THREAD_TEST_HPP_INCLUDED


#include "tri_engine.hpp"


class ThreadTestScene
    : public t3::Scene
{
public:
    ThreadTestScene();
    ~ThreadTestScene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(t3::tick_t delta_time) override;
    void suspendScene(t3::tick_t delta_time) override;
    
private:
    class SceneContext;
    std::unique_ptr<SceneContext> context_;

};

#endif // THREAD_TEST_HPP_INCLUDED