#include "tri_scene_node.hpp"
#include "tri_scene_graph.hpp"
#include "tri_camera_node.hpp"


namespace t3 {
inline namespace gfx {



SceneNode::SceneNode(
    actor_id_t actor_id,
    std::string name,
    RenderPass render_pass,
    const mtx4_t* to,
    const mtx4_t* from
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
    const mtx4_t* to_world,
    const mtx4_t* from_world
){

    if (to_world) {
        properties_.to_world_ = *to_world;
    }
    else {
        properties_.to_world_ = mtx4_t::identity();
    }
    
    
    if (!from_world) {
        //  from_worldは設定されてない
        properties_.from_world_ = mtx4_t::makeInverseMatrix(properties_.from_world_);
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
                    
                    vec4_t world_pos(asn->concat_.getPosition());
                    mtx4_t from_world = scene_graph->getCamera()->getProperties()->getFromWorldMatrix();
                    vec4_t screen_pos = from_world.xform(world_pos);
                    scene_graph->addAlphaSceneNode(asn);
                }
            }
            node->renderChildren(scene_graph);
        }
        node->postRender(scene_graph);
        it++;
    }
}

bool SceneNode::addChild(
    std::shared_ptr<ISceneNode> kid
) {
    children_.push_back(kid);
    
    vec3_t kid_pos = kid->getProperties()->getToWorldMatrix().getPosition();
    vec3_t dir = kid_pos - properties_.getToWorldMatrix().getPosition();
    
    float new_radius = dir.length() + kid->getProperties()->getRadius();
    
    if (new_radius > properties_.radius_) {
        properties_.radius_ = new_radius;
    }
    
    return true;
}


bool SceneNode::removeChild(
    actor_id_t id
) {

	for (SceneNodeList::iterator it = children_.begin(); it != children_.end(); ++it) {
	
		const SceneNodeProperties* prop = (*it)->getProperties();
		if (id == prop->getActorId()) {
			it = children_.erase(it);
			return true;
		}
	}
	return false;

}






}   // namespace gfx
}   // namespace t3