
#include "tri_camera_node.hpp"
#include "tri_scene_graph.hpp"

namespace t3 {
inline namespace gfx {

CameraNode::CameraNode(node_id_t id)
    : SceneNode(
        id,
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


std::shared_ptr<CameraNode> CameraNode::create(
    node_id_t id
) {
    std::shared_ptr<CameraNode> node;
    node.reset(new CameraNode(id));
    return node;
}



}   // namespace gfx
}   // namespace t3