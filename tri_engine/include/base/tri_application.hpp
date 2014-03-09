#ifndef TRI_APPLICATION_HPP_INCLUDED
#define TRI_APPLICATION_HPP_INCLUDED


#include "../util/tri_uncopyable.hpp"
#include <memory>
#include "tri_types.hpp"

class ApplicationDebugMenu;



namespace t3 {
void initializeTriEngine(
    const int width,
    const int height,
    const char* const title
);

void updateTriEngine();
void renderTriEngine();

void terminateTriEngine();

inline namespace base{

class SceneGenerator;

class Application
{

public:
    explicit Application( SceneGenerator* root_scene_generator );
    ~Application();

public:
    void initializeApplication();
    void updateApplication();
    void renderApplication();
    void terminateApplication();
    bool isActive() const;
    
private:
    void beginRender();
    void endRender();
    bool isDebugMenuOpenRequest();
    bool isSuspend() const;

public:
    void gotoRootScene();
    
    
private:
    std::unique_ptr<ApplicationDebugMenu> system_menu_;
    SceneGenerator* root_scene_generator_;
    uint32_t last_scene_change_frame_;
};


}   // namespace base
}   // namespace t3

#endif // TRI_APPLICATION_HPP_INCLUDED
