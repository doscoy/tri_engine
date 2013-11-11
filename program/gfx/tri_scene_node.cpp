#include "tri_scene_node.hpp"
#include "tri_scene_graph.hpp"
#include "tri_camera_node.hpp"


namespace t3 {
inline namespace gfx {



SceneNode::SceneNode(
    node_id_t actor_id,
    std::string name,
    RenderPass render_pass,
    const Mtx4* to,
    const Mtx4* from
)   : children_()
    , parent_(nullptr)
    , properties_(
        actor_id,
        name,
        render_pass,
        ALPHA_OPAQUE
) {
    setTransformMatrix(to, from);
    setRadius(0.0f);
}
    

SceneNode::~SceneNode()
{

}


void SceneNode::setTransformMatrix(
    const Mtx4* to_world,
    const Mtx4* from_world
){

    if (to_world) {
        properties_.to_world_ = *to_world;
    }
    else {
        properties_.to_world_ = Mtx4::getIdentity();
    }
    
    
    if (!from_world) {
        //  from_worldは設定されてない
        Mtx4::makeInverseMatrix(
            properties_.from_world_,
            properties_.to_world_
        );
    }
    else {
        properties_.from_world_ = *from_world;
    }
}


void SceneNode::onRestore(
    t3::SceneGraph* scene_graph
) {
    SceneNodeList::iterator it = children_.begin();
    SceneNodeList::iterator end = children_.end();
    
    while (it != end) {
        (*it)->onRestore(scene_graph);
        it++;
    }
}


void SceneNode::onUpdate(
    t3::SceneGraph* scene_graph,
    tick_t tick
) {
    SceneNodeList::iterator it = children_.begin();
    SceneNodeList::iterator end = children_.end();
    
    while (it != end) {
        (*it)->onUpdate(scene_graph, tick);
        it++;
    }
}


bool SceneNode::preRender(
    t3::SceneGraph* scene_graph
) {
    T3_TRACE("SceneNode::preRender() - %s\n", getNodeName());
    scene_graph->pushAndSetMatrix(properties_.to_world_);
    
    return true;
}

void SceneNode::postRender(t3::SceneGraph *scene_graph) {
    scene_graph->popMatrix();
}

bool SceneNode::isVisible(t3::SceneGraph *scene_graph) const
{

    // フラスタムによる可視判定を書く

    return true;
}


void SceneNode::render(t3::SceneGraph *scene_graph)
{

    properties_.material_.use();

    
}

void SceneNode::renderChildren(t3::SceneGraph *scene_graph)
{
    SceneNodeList::iterator it = children_.begin();
    SceneNodeList::iterator end = children_.end();
    
    while (it != end) {
        std::shared_ptr<ISceneNode> node = (*it);
        if (node->preRender(scene_graph)) {
            //  prerenderでfalseだったらレンダリングは省略できる
            
            if (node->isVisible(scene_graph)) {
                uint8_t opacity = node->getProperties()->material_.getOpacity();
                if (opacity == 255) {
                    //  完全な不透明
                    node->render(scene_graph);
                }
                else if (opacity > 0) {
                    //  完全な透明ではない。つまり半透明
                    AlphaSceneNode* asn = new AlphaSceneNode;
                    T3_NULL_ASSERT(asn);
                    
                    asn->node_ = node;
                    asn->concat_ = *scene_graph->getTopMatrix();
                    
                    Vec4 world_pos(asn->concat_.getPosition());
                    Mtx4 from_world = scene_graph->getCamera()->getProperties()->getFromWorldMatrix();
                    Vec4 screen_pos = from_world.xform(world_pos);
                    scene_graph->addAlphaSceneNode(asn);
                }
            }
            node->renderChildren(scene_graph);
        }
        node->postRender(scene_graph);
        it++;
    }
}

void SceneNode::detachParent(
    std::shared_ptr<ISceneNode> kid
) {
    ISceneNode* kid_parent = kid->getParent();
    if (kid_parent) {
        node_id_t kid_id = kid->getProperties()->getNodeID();
        kid_parent->removeChild(kid_id);
    }
}

bool SceneNode::addChild(
    std::shared_ptr<ISceneNode> kid
) {
    if (kid->getParent() == this) {
        return true;
    }
    
    detachParent(kid);
    
    children_.push_back(kid);
    kid->setParent(this);
    
    Vec3 kid_pos = kid->getProperties()->getToWorldMatrix().getPosition();
    Vec3 dir = kid_pos - properties_.getToWorldMatrix().getPosition();
    
    float new_radius = dir.length() + kid->getProperties()->getRadius();
    
    if (new_radius > properties_.radius_) {
        properties_.radius_ = new_radius;
    }
    
    return true;
}


bool SceneNode::removeChild(
    node_id_t id
) {

	for (SceneNodeList::iterator it = children_.begin(); it != children_.end(); ++it) {
	
		const SceneNodeProperties* prop = (*it)->getProperties();
		if (id == prop->getNodeID()) {
			it = children_.erase(it);
			return true;
		}
	}
	return false;

}






}   // namespace gfx
}   // namespace t3