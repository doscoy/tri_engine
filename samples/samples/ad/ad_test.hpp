
#ifndef AD_TEST_HPP_INCLUDED
#define AD_TEST_HPP_INCLUDED


#include "tri_engine.hpp"


class AdScene
    : public t3::SceneBase
{
public:
    AdScene();
    ~AdScene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(t3::tick_t delta_time) override;
    void suspendScene(t3::tick_t delta_time) override;
    
private:
    class SceneContext;
    t3::ScopedPtr<SceneContext> context_;

};

#endif // AD_TEST_HPP_INCLUDED
