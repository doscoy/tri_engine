

#ifndef dev_t3_tri_camera_node_hpp
#define dev_t3_tri_camera_node_hpp

#include "tri_scene_node.hpp"
#include "tri_camera.hpp"


namespace t3 {
inline namespace gfx {

class SceneGraph;

class CameraNode
    : public SceneNode
{
public:
    CameraNode();
    virtual ~CameraNode();

public:
    virtual void setViewTransform(SceneGraph* scene_graph);
    
    virtual bool isVisible(SceneGraph* scene_graph) const override {
        return active_;
    }
    
    virtual void render(SceneGraph* scene_graph);
    
protected:
    Camera camera_;
    bool debug_camera_;
    bool active_;
};

}   // gfx
}   // t3



#endif
