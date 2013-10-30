

#ifndef dev_t3_tri_camera_node_hpp
#define dev_t3_tri_camera_node_hpp

#include "tri_scene_node.hpp"



namespace t3 {
inline namespace gfx {

class SceneGraph;

class CameraNode
    : public SceneNode
{
public:
    void setViewTransform(SceneGraph* scene_graph);
};

}   // gfx
}   // t3



#endif
