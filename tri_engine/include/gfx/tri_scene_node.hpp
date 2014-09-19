
#ifndef dev_t3_tri_scene_node_h
#define dev_t3_tri_scene_node_h

#include "../math/tri_math.hpp"
#include "base/tri_std.hpp"



namespace t3 {
inline namespace gfx {



using NodeID = uint32_t;


class SceneGraph;

class ISceneNode;
using SceneNodePtr = SharedPtr<ISceneNode>;

class ISceneNode
{
protected:

public:
    virtual NodeID getNodeID() const = 0;

    virtual void onUpdate(
        SceneGraph* scene,
        tick_t delta_time
    ) = 0;

    virtual bool preRender(
        SceneGraph* scene
    ) = 0;

    virtual bool isVisible(SceneGraph* scene_graph) const = 0;


    virtual void render(SceneGraph* scene_graph) = 0;
    
    virtual void renderChildren(SceneGraph* scene_graph) = 0;
    
    virtual void postRender(SceneGraph* scene_graph) = 0;
    
    virtual bool addChild(
        SceneNodePtr kid
    ) = 0;
    
    virtual bool removeChild(
        NodeID id
    ) = 0;
    
    virtual ISceneNode* getParent() = 0;
    virtual const ISceneNode* getParent() const = 0;
    virtual void setParent(ISceneNode* p) = 0;
    
    virtual ~ISceneNode(){}
    
};


using SceneNodeList = Vector<SceneNodePtr>;

using RenderableSceneNodes = List<SceneNodePtr>;







}   // namespace gfx
}   // namespace t3

#endif
