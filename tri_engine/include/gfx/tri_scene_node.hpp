
#ifndef dev_t3_tri_scene_node_h
#define dev_t3_tri_scene_node_h

#include "../math/tri_math.hpp"
#include <memory>
#include <vector>
#include <list>



namespace t3 {
inline namespace gfx {




typedef uint32_t node_id_t;

extern node_id_t getNewNodeID();

class SceneGraph;


class ISceneNode
{
protected:

public:
    virtual node_id_t getNodeID() const = 0;

    virtual void onUpdate(
        SceneGraph* scene,
        tick_t tick
    ) = 0;

    virtual bool preRender(
        SceneGraph* scene
    ) = 0;

    virtual bool isVisible(SceneGraph* scene_graph) const = 0;


    virtual void render(SceneGraph* scene_graph) = 0;
    
    virtual void renderChildren(SceneGraph* scene_graph) = 0;
    
    virtual void postRender(SceneGraph* scene_graph) = 0;
    
    virtual bool addChild(
        std::shared_ptr<ISceneNode> kid
    ) = 0;
    
    virtual bool removeChild(
        node_id_t id
    ) = 0;
    
    virtual ISceneNode* getParent() = 0;
    virtual const ISceneNode* getParent() const = 0;
    virtual void setParent(ISceneNode* p) = 0;
    
    virtual ~ISceneNode(){}
    
};




typedef std::vector<std::shared_ptr<ISceneNode>> SceneNodeList;

typedef std::list<ISceneNode*> RenderableSceneNodes;







}   // namespace gfx
}   // namespace t3

#endif
