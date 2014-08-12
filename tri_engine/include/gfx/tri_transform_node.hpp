
#ifndef TRI_TRANSFORM_NODE_HPP_INCLUDED
#define TRI_TRANSFORM_NODE_HPP_INCLUDED


#include "tri_scene_node.hpp"

namespace t3 {
inline namespace gfx {

class Entity;

class TransformNode
    : public ISceneNode
{
public:
    TransformNode(
        node_id_t id,
        std::string name
    );
    virtual~ TransformNode();
    
public:
    static std::shared_ptr<TransformNode> create(
        std::string name
    );
    
public:
    virtual node_id_t getNodeID() const {
        return node_id_;
    }

    void attachEntity(
        Entity* entity
    ) {
        entity_ = entity;
    }
    
    void detachEntity() {
        entity_ = nullptr;
    }
    
    bool hasEntity() const {
        return entity_ != nullptr;
    }
    
    void render(
        SceneGraph* scene_graph
    ) override;
    
    bool preRender(
        t3::SceneGraph* scene_graph
    ) override;
    
    void postRender(
        t3::SceneGraph* scene_graph
    ) override;
    
    virtual ISceneNode* getParent() {
        return parent_;
    }
    
    virtual const ISceneNode* getParent() const {
        return parent_;
    }
    
    
    virtual void setParent(
        ISceneNode* p
    ) {
        parent_ = p;
    }
    
    
    void onUpdate(
        SceneGraph* scene_graph,
        tick_t delta_time
    ) override;
    
    
    bool isVisible(SceneGraph* scene_graph) const override;
    
    
    virtual void renderChildren(
        SceneGraph* scene_graph
    );
    
    bool addChild(
        std::shared_ptr<ISceneNode> kid
    ) override;
    
    bool removeChild(
        node_id_t id
    ) override;
    
    
    void detachParent(
        std::shared_ptr<ISceneNode> kid
    );
    
    

    std::string getNodeName() const {
        return std::string();
    }

    std::shared_ptr<TransformNode> createNode(
        std::string name
    );


public:
    void position(
        float x,
        float y,
        float z
    ) {
        calc_request_ = true;
        position_.x_ = x;
        position_.y_ = y;
        position_.z_ = z;
    }
    
    void position(
        const Vec3& v
    ) {
        calc_request_ = true;
        position_ = v;
    }
    
    const Vec3& position() const {
        return position_;
    }
    
    void addPosition(
        const Vec3& v
    ) {
        calc_request_ = true;
        position_ += v;
    }
    
    void addPositionX(
        const float v
    ) {
        calc_request_ = true;
        position_.x_ += v;
    }
    
    void addPositionY(
        const float v
    ) {
        calc_request_ = true;
        position_.y_ += v;
    }
    void addPositionZ(
        const float v
    ) {
        calc_request_ = true;
        position_.z_ += v;
    }
    
    void rotation(
        float x,
        float y,
        float z
    ) {
        calc_request_ = true;
        rotation_.x_ = x;
        rotation_.y_ = y;
        rotation_.z_ = z;
    }
    
    
    void setRotationX(
        const float r
    ) {
        calc_request_ = true;
        rotation_.x_ = r;
    }
    
    void setRotationY(
        const float r
    ) {
        calc_request_ = true;
        rotation_.y_ = r;
    }
    
    void setRotationZ(
        const float r
    ) {
        calc_request_ = true;
        rotation_.z_ = r;
    }
    
    void rotation(
        const Vec3& v
    ) {
        calc_request_ = true;
        rotation_ = v;
    }
    
    const Vec3& rotation() const {
        return rotation_;
    }
    
    void addRotationX(
        const float r
    ) {
        calc_request_ = true;
        rotation_.x_ += r;
    }
    
    void addRotationY(
        const float r
    ) {
        calc_request_ = true;
        rotation_.y_ += r;
    }
    
    void addRotationZ(
        const float r
    ) {
        calc_request_ = true;
        rotation_.z_ += r;
    }
    
    void scale(
        float x,
        float y,
        float z
    ) {
        calc_request_ = true;
        scale_.x_ = x;
        scale_.y_ = y;
        scale_.z_ = z;
    }
    
    void scale(
        const Vec3& v
    ) {
        calc_request_ = true;
        scale_ = v;
    }
    
    const Vec3& scale() const {
        return scale_;
    }
    
    void setVisible(
        const bool visible
    ) {
        visible_ = visible;
    }

    bool isVisible() const {
        return visible_;
    }

    const Mtx44* getTransformMatrix();

private:
    void makeTransformMatrix();


private:
    Vec3 position_;
    Vec3 rotation_;
    Vec3 scale_;
    bool visible_;
    Mtx44 transform_;
    bool calc_request_;
    Entity* entity_;
    SceneNodeList children_;
    ISceneNode* parent_;
    node_id_t node_id_;
};

}   // namespace gfx
}   // namespace t3


#endif // TRI_TRANSFORM_NODE_HPP_INCLDED
