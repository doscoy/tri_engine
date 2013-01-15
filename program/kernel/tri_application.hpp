#ifndef TRI_APPLICATION_HPP_INCLUDED
#define TRI_APPLICATION_HPP_INCLUDED


#include "../util/tri_uncopyable.hpp"
#include "tri_develop_base.hpp"
#include <memory>


class ApplicationDebugMenu;

namespace t3 {
inline namespace core{
class SceneGenerator;
}
class Application
{
public:
    static int run( SceneGenerator* root_scene_generator );
    
private:
    explicit Application( SceneGenerator* root_scene_generator );
    ~Application();

private:
    void initializeApplication();
    void update(tick_t tick);
    void beginRender();
    void endRender();
    SceneGenerator* root_scene_generator_;
    bool isDebugMenuOpenRequest();
    bool isSuspend() const;

public:
    void gotoRootScene();
    
    
private:
    std::unique_ptr<ApplicationDebugMenu> system_menu_;
};



}   // namespace t3

#endif // TRI_APPLICATION_HPP_INCLUDED
