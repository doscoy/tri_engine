
#ifndef TRI_TEST_OBJECT_NODE_HPP_INCLUDED
#define TRI_TEST_OBJECT_NODE_HPP_INCLUDED

#include "tri_scene_node.hpp"
#include "../theater/tri_box.hpp"



namespace t3 {
inline namespace gfx {

class TestObjectNode
    : public SceneNode
{
public:
    TestObjectNode(
        node_id_t id
    );
    virtual ~TestObjectNode();
    
    
public:
    virtual void render(
        SceneGraph* scene_graph
    );
    
    void setColor(const Color& c) {
        color_ = c;
    }

    static std::shared_ptr<TestObjectNode> create(node_id_t id);

private:
    Box box_;
    t3::Color color_;
};

}   // namespace gfx
}   // namespace t3



#endif // TRI_TEST_OBJECT_NODE_HPP_INCLUDE