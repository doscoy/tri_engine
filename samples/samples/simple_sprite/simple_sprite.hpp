////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

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
    void updateScene(const t3::DeltaTime delta_time) override;

private:
    class SceneContext;
    t3::UniquePtr<SceneContext> context_;

};

#endif // SIMPLE_SPRITE_HPP_INCLUDED
