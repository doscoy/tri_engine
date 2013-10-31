
#include "tri_camera_node.hpp"
#include "tri_scene_graph.hpp"

namespace t3 {
inline namespace gfx {

CameraNode::CameraNode()
    : SceneNode(
        0,
        "Camera",
        RENDER_PASS_0,
        nullptr
    )
    , debug_camera_(false)
    , active_(true)
{
    
}


CameraNode::~CameraNode()
{}

void CameraNode::setViewTransform(
    SceneGraph* scene_graph
) {
    
}

void CameraNode::render(SceneGraph* scene_graph)
{
    if (debug_camera_) {
        camera_.getFrustom();
    }
}




}   // namespace gfx
}   // namespace t3