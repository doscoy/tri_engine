
#ifndef SANDBOX_TEMPLATE_HPP_INCLUDED
#define SANDBOX_TEMPLATE_HPP_INCLUDED


#include "tri_engine.hpp"


class TemplateScene
    : public t3::SceneBase
{
public:
    TemplateScene();
    ~TemplateScene();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(t3::tick_t delta_time) override;
    void suspendScene(t3::tick_t delta_time) override;
    
private:
    class SceneContext;
    t3::ScopedPtr<SceneContext> context_;

};

#endif // SANDBOX_TEMPLATE_HPP_INCLUDED
