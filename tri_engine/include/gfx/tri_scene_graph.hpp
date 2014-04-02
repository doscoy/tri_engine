//
//  tri_scene_graph.hpp
//  dev_t3
//
//  Created by 哲郎 可児 on 12/05/24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef dev_t3_tri_scene_graph_hpp
#define dev_t3_tri_scene_graph_hpp

#include <map>
#include <memory.h>

#include "../math/tri_matrix_stack.hpp"
#include "tri_transform_node.hpp"
#include "tri_scene_node.hpp"
#include "tri_camera.hpp"
namespace t3 {
inline namespace gfx {



typedef std::map<node_id_t, std::shared_ptr<ISceneNode>> SceneNodeMap;


class TestObjectNode;
class CameraNode;
class SkyNode;

class SceneGraph
{
public:

    SceneGraph();
    virtual ~SceneGraph();
    
    
public:
    void setupView();
    void renderScene();
    
    void updateScene(tick_t delta_time);
    
    std::shared_ptr<ISceneNode> findNode( node_id_t id );
    
    
    void setCamera(
        std::shared_ptr<Camera> cam
    ) {
        camera_ = cam;
    }
    
    const std::shared_ptr<Camera> getCamera() const {
        return camera_;
    }
    
    const std::shared_ptr<TransformNode> getRootNode() const {
        return root_;
    }
    
    void pushAndSetMatrix(
        const Mtx4& to_world
    );
    
    void popMatrix();
    
    const Mtx4* getTopMatrix();
    
    std::shared_ptr<TransformNode> createNode();
    
private:

    bool addChild(
        node_id_t id,
        std::shared_ptr<TransformNode> kid
    ) {
        node_map_[id] = kid;
        return root_->addChild(kid);
    }

    bool removeChild(
        node_id_t id
    ) {
        node_map_.erase(id);
        return root_->removeChild(id);
    }


protected:
    std::shared_ptr<TransformNode> root_;
    std::shared_ptr<Camera> camera_;
    
    MatrixStack matrix_stack_;
    SceneNodeMap node_map_;
    
};


}   // namespace gfx
}   // namespace t3


#endif
