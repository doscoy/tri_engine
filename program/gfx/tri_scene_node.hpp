
#ifndef dev_t3_tri_scene_node_h
#define dev_t3_tri_scene_node_h

#include "../math/tri_math.hpp"
#include "tri_scene_node_properties.hpp"
#include <memory>
#include <vector>
#include <list>


namespace t3 {
inline namespace gfx {

class SceneGraph;


class ISceneNode
{
protected:

public:
    virtual const SceneNodeProperties* const getProperties() const = 0;

    virtual void setTransformMatrix(
        const Mtx4* toWorld,
        const Mtx4* fromWorld = nullptr
    ) = 0;

    virtual void onUpdate(
        SceneGraph* scene,
        tick_t tick
    ) = 0;
    
    virtual void onRestore(
        SceneGraph* scene
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
        actor_id_t id
    ) = 0;
    
    
    
    virtual ~ISceneNode(){}
    
};




typedef std::vector<std::shared_ptr<ISceneNode>> SceneNodeList;


class SceneNode : public ISceneNode
{
    friend class SceneGraph;
    
protected:
    SceneNodeList children_;
    SceneNode* parent_;
    SceneNodeProperties properties_;


public:
    SceneNode(
        actor_id_t actor_id,
        std::string name,
        RenderPass render_pass,
        const Mtx4* to,
        const Mtx4* from = nullptr
    );
    
    virtual ~SceneNode();
    
public:
    virtual const SceneNodeProperties* const getProperties() const override {
        return &properties_;
    }
    
    virtual void setTransformMatrix(
        const Mtx4* to_world,
        const Mtx4* from_world = nullptr
    ) override;
    
    virtual void onRestore(
        SceneGraph* scene_graph
    ) override;
    
    virtual void onUpdate(
        SceneGraph* scene_graph,
        tick_t tick
    ) override;
    
    
    virtual bool preRender(
        SceneGraph* scene_graph
    ) override;
    
    virtual bool isVisible(SceneGraph* scene_graph) const override;
    
    virtual void render(
        SceneGraph* scene_graph
    ) override;
    
    
    virtual void renderChildren(
        SceneGraph* scene_graph
    );
    
    virtual void postRender(
        SceneGraph* scene_graph
    ) override;
    
    virtual bool addChild(
        std::shared_ptr<ISceneNode> kid
    ) override;
    
    virtual bool removeChild(
        actor_id_t id
    ) override;
    
    
    void setOpacity(
        const float opacity
    ) {
        properties_.setOpacity(opacity);
    }

    Vec3 getPosition() const {
        return properties_.getToWorldMatrix().getPosition();
    }

    void setPosition(Vec3& pos) {
        properties_.getToWorldMatrix().setPosition(
            pos.x,
            pos.y,
            pos.z
        );
    }
    
    void setRadius(
        const float radius
    ) {
        properties_.radius_ = radius;
    }

    void setMaterial(
        const Material& material
    ) {
        properties_.material_ = material;
    }

    const char* getNodeName() const {
        return properties_.name_.c_str();
    }

};




class AlphaSceneNode
{
public:
    std::shared_ptr<ISceneNode> node_;
    Mtx4 concat_;
    float screen_z_;
    
    bool const operator < (const AlphaSceneNode& other) {
        return screen_z_ < other.screen_z_;
    }

};

typedef std::list<AlphaSceneNode*> AlphaSceneNodes;







}   // namespace gfx
}   // namespace t3

#endif
