//
//  tri_scene_node_properties.hpp
//  dev_t3
//
//  Created by 哲郎 可児 on 12/05/23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef dev_t3_tri_scene_node_properties_hpp
#define dev_t3_tri_scene_node_properties_hpp

#include "../math/tri_math.hpp"
#include "tri_material.hpp"
#include <string>

namespace t3 {
inline namespace gfx {

typedef uint32_t node_id_t;

enum RenderPass {
    RENDER_PASS_0,                          // 開始パス
    RENDER_PASS_STATIC = RENDER_PASS_0,     // 環境とレベルジオメトリ
    RENDER_PASS_DYNAMIC,                    // 移動可能オブジェクト
    RENDER_PASS_SKY,                        // 遠景
    RENDER_PASS_LAST,                       // ループカウンタ
};


enum AlphaType {
    ALPHA_MATERIAL,
    ALPHA_OPAQUE,
    NORMAL_MATERIAL,
};

class SceneNodeProperties
{
    friend class SceneNode;
    
public:
    SceneNodeProperties(
        node_id_t id,
        std::string name,
        RenderPass render_pass,
        AlphaType alpha_type
    );
    
protected:
    node_id_t actor_id_;
    std::string name_;
    Mtx4 to_world_;
    Mtx4 from_world_;
    float radius_;
    RenderPass render_pass_;
    Material material_;
    AlphaType alpha_type_;
    
    
    void setOpacity(
        const float alpha
    ) {
        alpha_type_ = ALPHA_MATERIAL;
        material_.setOpacity(alpha);
    }
    
public:
    const node_id_t getActorId() const {
        return actor_id_;
    }
    
    const Mtx4& getToWorld() const {
        return to_world_;
    }
    
    const Mtx4& getFromWorld() const {
        return from_world_;
    }
    
    void getTransformMatrix(
        Mtx4* to_world,
        Mtx4* from_world
    ) const;
    
    const char* getName() const {
        return name_.c_str();
    }
    
    bool hasAlpha() const {
        return material_.hasAlpha();
    }
    
    virtual float getOpacity() const {
        return material_.getOpacity();
    }
    
    RenderPass getRenderPass() const {
        return render_pass_;
    }
    
    float getRadius() const {
        return radius_;
    }
    
    Mtx4& getToWorldMatrix() {
        return to_world_;
    }
    
    const Mtx4& getToWorldMatrix() const {
        return to_world_;
    }
    
    Mtx4& getFromWorldMatrix() {
        return from_world_;
    }
    
    const Mtx4& getFromWorldMatrix() const {
        return from_world_;
    }
    
    
    const Material& getMaterial() const {
        return material_;
    }
    
    
    
};


}   // namespace gfx
}   // namespace t3

#endif
