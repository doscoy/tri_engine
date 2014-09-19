
#ifndef EVENT_HANDLING_HPP_INCLUDED
#define EVENT_HANDLING_HPP_INCLUDED


#include "tri_engine.hpp"


class EventHandlingScene
    : public t3::Scene
{
public:
    EventHandlingScene();
    ~EventHandlingScene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(t3::tick_t delta_time) override;
    void suspendScene(t3::tick_t delta_time) override;
    
private:
    class SceneContext;
    t3::ScopedPtr<SceneContext> context_;

};

#endif // EVENT_HANDLING_HPP_INCLUDED
