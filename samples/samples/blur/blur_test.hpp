////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#ifndef BLUR_TEST_HPP_INCLUDED
#define BLUR_TEST_HPP_INCLUDED


#include "tri_engine.hpp"


class BlurScene
    : public t3::SceneBase
{
public:
    BlurScene();
    ~BlurScene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(const t3::DeltaTime delta_time) override;
private:
    class SceneContext;
    t3::ScopedPtr<SceneContext> context_;

};

#endif // BLUR_TEST_HPP_INCLUDED
