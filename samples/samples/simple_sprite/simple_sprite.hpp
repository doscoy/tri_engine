
#ifndef SIMPLE_SPRITE_HPP_INCLUDED
#define SIMPLE_SPRITE_HPP_INCLUDED


#include "tri_engine.hpp"


class SimpleSpriteScene
    : public t3::Scene
{
public:
    SimpleSpriteScene();
    ~SimpleSpriteScene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(t3::tick_t tick) override;

private:
    class SceneContext;
    std::unique_ptr<SceneContext> context_;

};

#endif // SIMPLE_SPRITE_HPP_INCLUDED
