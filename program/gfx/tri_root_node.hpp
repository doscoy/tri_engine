
#ifndef TRI_ROOT_NODE_HPP_INCLUDED
#define TRI_ROOT_NODE_HPP_INCLUDED

#include "tri_scene_node.hpp"

namespace t3 {
inline namespace gfx {

class RootNode
    : public SceneNode
{
public:
    RootNode();
    
public:
    virtual bool addChild(std::shared_ptr<ISceneNode> kid) override;
    
    virtual void renderChildren(SceneGraph* scene_graph) override;
    
    virtual bool isVisible(SceneGraph* scene_graph) const {
        return true;
    }
    

};

}
}



#endif // TRI_ROOT_NODE_HPP_INCLUDE