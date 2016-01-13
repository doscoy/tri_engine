////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#ifndef UI_BUTTON_TEST_HPP_INCLUDED
#define UI_BUTTON_TEST_HPP_INCLUDED


#include "tri_engine.hpp"


class UiButtonScene
    : public t3::SceneBase
{
public:
    UiButtonScene();
    ~UiButtonScene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(const t3::DeltaTime delta_time) override;
    
private:
    class SceneContext;
    t3::UniquePtr<SceneContext> context_;

};

#endif // UI_BUTTON_TEST_HPP_INCLUDED
