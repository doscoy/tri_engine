#include "tri_root_node.hpp"

namespace t3 {
inline namespace gfx {

RootNode::RootNode()
    : SceneNode(
        0,
        "Root",
        RENDER_PASS_0,
        nullptr
    )
{
    
    
}

bool RootNode::addChild(
    std::shared_ptr<ISceneNode> kid
) {

    return true;
}


void RootNode::renderChildren(
    SceneGraph* scene_graph
) {

}




}   // namespace gfx
}   // namespace t3
