#include "tri_root_node.hpp"

namespace t3 {
inline namespace gfx {

RootNode::RootNode(node_id_t id)
    : SceneNode(
        id,
        "Root",
        RENDER_PASS_0,
        nullptr
    )
{
    children_.reserve(RENDER_PASS_LAST);
    
    std::shared_ptr<SceneNode> static_group(
        new SceneNode(
            0,
            "StaticGroup",
            RENDER_PASS_STATIC,
            nullptr
        )
    );
    children_.push_back(static_group);
    
    std::shared_ptr<SceneNode> actor_group(
        new SceneNode(
            0,
            "DynamicGroup",
            RENDER_PASS_DYNAMIC,
            nullptr
        )
    );
    children_.push_back(actor_group);
    
    std::shared_ptr<SceneNode> sky_group(
        new SceneNode(
            0,
            "SkyGroup",
            RENDER_PASS_SKY,
            nullptr
        )
    );
    children_.push_back(sky_group);
    
}

bool RootNode::addChild(
    std::shared_ptr<ISceneNode> kid
) {
    if (kid->getParent() == this) {
        return true;
    }
    
    //  子はシーングラフをレンダリングパスで分ける
    //  シーンノードはレンダリングパスの値に基づき子のどれかに追加
    int kid_render_pass = kid->getProperties()->getRenderPass();
    T3_ASSERT(children_[kid_render_pass]);
    
    detachParent(kid);
    kid->setParent(this);
    
    return children_[kid_render_pass]->addChild(kid);
}


void RootNode::renderChildren(
    SceneGraph* scene_graph
) {
    for (int pass = RENDER_PASS_0; pass < RENDER_PASS_LAST; ++pass) {
        switch (pass) {
            case RENDER_PASS_STATIC:
            case RENDER_PASS_DYNAMIC:
                children_[pass]->renderChildren(scene_graph);
                break;
            
            case RENDER_PASS_SKY:
                // 最後に書くからzバッファへの書き込みは必要無い
                children_[pass]->renderChildren(scene_graph);
                break;
        }
    }
}

std::shared_ptr<RootNode> RootNode::create(
    node_id_t id
) {
    std::shared_ptr<RootNode> node;
    node.reset(new RootNode(id));
    return node;
}





}   // namespace gfx
}   // namespace t3
