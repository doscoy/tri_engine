
#ifndef AUDIO_TEST_HPP_INCLUDED
#define AUDIO_TEST_HPP_INCLUDED


#include "tri_engine.hpp"


class AudioTestScene
    : public t3::SceneBase
{
public:
    AudioTestScene();
    ~AudioTestScene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(t3::tick_t delta_time) override;
    void suspendScene(t3::tick_t delta_time) override;
    
private:
    class SceneContext;
    t3::ScopedPtr<SceneContext> context_;

};

#endif // AUDIO_TEST_HPP_INCLUDED
