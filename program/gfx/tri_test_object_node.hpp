
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
        actor_id_t id,
        std::string name
    );
    virtual ~TestObjectNode();
    
    
public:
    virtual void render(SceneGraph* scene_graph);

private:
    Box box_;
};

}   // namespace gfx
}   // namespace t3



#endif // TRI_TEST_OBJECT_NODE_HPP_INCLUDE