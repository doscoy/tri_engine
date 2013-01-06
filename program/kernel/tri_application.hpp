#ifndef TRI_APPLICATION_HPP_INCLUDED
#define TRI_APPLICATION_HPP_INCLUDED


#include "../util/tri_uncopyable.hpp"
#include "tri_develop_base.hpp"

namespace t3 {
inline namespace core{
class SceneGenerator;
}
class Application
    : private Uncopyable
{
public:
    explicit Application( SceneGenerator* root_scene_generator );
    ~Application();

public:
    void initializeApplication();
    void update(tick_t tick);
    void beginRender();
    void endRender();
    SceneGenerator* root_scene_generator_;
    
private:
    bool isDebugMenuOpenRequest();
    bool isSuspend() const;
};



}   // namespace t3

#endif // TRI_APPLICATION_HPP_INCLUDED
