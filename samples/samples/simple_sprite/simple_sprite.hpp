
#ifndef SIMPLE_SPRITE_HPP_INCLUDED
#define SIMPLE_SPRITE_HPP_INCLUDED


#include "tri_engine.hpp"


class SimpleSpriteScene
    : public t3::SceneBase
{
public:
    SimpleSpriteScene();
    ~SimpleSpriteScene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(t3::tick_t delta_time) override;
    void suspendScene(t3::tick_t delta_time) override;
private:
    class SceneContext;
    t3::ScopedPtr<SceneContext> context_;

};

#endif // SIMPLE_SPRITE_HPP_INCLUDED
