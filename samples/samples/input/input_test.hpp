////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

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
    void updateScene(const t3::DeltaTime delta_time) override;
    void debugRenderScene() override;
    
private:
    class SceneContext;
    t3::ScopedPtr<SceneContext> context_;

};

#endif // INPUT_TEST_HPP_INCLUDED
