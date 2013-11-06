
#ifndef TRI_ROOT_NODE_HPP_INCLUDED
#define TRI_ROOT_NODE_HPP_INCLUDED

#include "tri_scene_node.hpp"

namespace t3 {
inline namespace gfx {

class RootNode
    : public SceneNode
{
private:
    RootNode();
    explicit RootNode(node_id_t id);
    
    
public:
    virtual bool addChild(std::shared_ptr<ISceneNode> kid) override;
    
    virtual void renderChildren(SceneGraph* scene_graph) override;
    
    virtual bool isVisible(SceneGraph* scene_graph) const {
        return true;
    }
    
    static std::shared_ptr<RootNode> create(
        node_id_t id
    );

};

}
}



#endif // TRI_ROOT_NODE_HPP_INCLUDE