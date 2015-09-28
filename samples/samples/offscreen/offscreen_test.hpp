////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#ifndef OFFSCREEN_HPP_INCLUDED
#define OFFSCREEN_HPP_INCLUDED


#include "tri_engine.hpp"


class OffscreenTestScene
    : public t3::SceneBase
{
public:
    OffscreenTestScene();
    ~OffscreenTestScene();
    
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

#endif // SANDBOX_TEMPLATE_HPP_INCLUDED


