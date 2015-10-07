////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#ifndef ZIP_TEST_HPP_INCLUDED
#define ZIP_TEST_HPP_INCLUDED


#include "tri_engine.hpp"


class ZipTestScene
    : public t3::SceneBase
{
public:
    ZipTestScene();
    ~ZipTestScene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(t3::DeltaTime delta_time) override;

    
private:
    class SceneContext;
    t3::ScopedPtr<SceneContext> context_;
};

#endif // ZIP_TEST_HPP_INCLUDED
