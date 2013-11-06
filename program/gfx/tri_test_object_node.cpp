#include "tri_test_object_node.hpp"


namespace t3 {
inline namespace gfx {


TestObjectNode::TestObjectNode(
    node_id_t id
)   : SceneNode(
        id,
        "TestObj",
        RENDER_PASS_DYNAMIC,
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


std::shared_ptr<TestObjectNode> TestObjectNode::create(
    node_id_t id
) {
    std::shared_ptr<TestObjectNode> node;
    node.reset(new TestObjectNode(id));
    return node;
}


}   // namespace gfx
}   // namespace t3