////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#ifndef SANDBOX_TEMPLATE_HPP_INCLUDED
#define SANDBOX_TEMPLATE_HPP_INCLUDED


#include "tri_engine.hpp"


class FontTestScene
    : public t3::SceneBase
{
public:
    FontTestScene();
    ~FontTestScene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(t3::DeltaTime delta_time) override;
    void debugRenderScene() override;
private:
    class SceneContext;
    t3::ScopedPtr<SceneContext> context_;

};

#endif // SANDBOX_TEMPLATE_HPP_INCLUDED
