#include "tri_test_object_node.hpp"


namespace t3 {
inline namespace gfx {


TestObjectNode::TestObjectNode(
    actor_id_t id,
    std::string name
)   : SceneNode(
        id,
        name,
        RENDER_PASS_ACTOR,
        nullptr
      )
{
    box_.setSize(2,2,2);
}

TestObjectNode::~TestObjectNode()
{
    
}

void TestObjectNode::render(
    SceneGraph* scene_graph
) {

}

}   // namespace gfx
}   // namespace t3