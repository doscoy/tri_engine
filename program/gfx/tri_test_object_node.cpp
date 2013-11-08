#include "tri_test_object_node.hpp"
#include "../dbg/tri_dbg.hpp"

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
    drawPlane(
        t3::Vec3(0,0,0),
        t3::Vec3(0,1,0),
        t3::Vec3(2,2,2),
        t3::Color::orange()
    );
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