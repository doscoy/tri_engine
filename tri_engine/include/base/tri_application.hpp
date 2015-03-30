#ifndef TRI_APPLICATION_HPP_INCLUDED
#define TRI_APPLICATION_HPP_INCLUDED


#include "util/tri_uncopyable.hpp"
#include "base/tri_std.hpp"
#include "tri_types.hpp"
#include "util/tri_stopwatch.hpp"


class ApplicationDebugMenu;



namespace t3 {
void initializeTriEngine(
    const int width,
    const int height,
    const char* const title
);


void terminateTriEngine();

inline namespace base{

class SceneGenerator;

class Application
{

public:
    Application();
    virtual ~Application();


private:
    virtual void initializeGame() = 0;
    virtual void terminateGame() = 0;

public:
    void initializeApplication();
    void updateApplication();
    void renderApplication();
    void terminateApplication();
    bool isActive() const;

    void setRootScene(SceneGenerator* root) {
        root_scene_generator_ = root;
    }
    
private:
    void beginRender();
    void endRender();
    bool isDebugMenuOpenRequest();
    bool isSuspend() const;

    void initializeWorkBar();
    void debugPrinting();
public:
    void gotoRootScene();
    
    
private:
#if DEBUG
    ScopedPtr<ApplicationDebugMenu> system_menu_;
#endif
    SceneGenerator* root_scene_generator_;
    uint32_t last_scene_change_frame_;
    uint32_t memory_leak_check_filter_;
    Stopwatch fps_timer_;
    Array<float, 260> fps_stack_;
    float fps_;
};


void setApplication(Application& app);
void initializeApplication();
void terminateApplication();
void updateApplication();
void renderApplication();



}   // namespace base
}   // namespace t3

#endif // TRI_APPLICATION_HPP_INCLUDED
