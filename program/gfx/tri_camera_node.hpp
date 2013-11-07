

#ifndef dev_t3_tri_camera_node_hpp
#define dev_t3_tri_camera_node_hpp

#include "tri_scene_node.hpp"
#include "tri_camera.hpp"


namespace t3 {
inline namespace gfx {

class SceneGraph;

class CameraNode
    : public SceneNode
{
private:
    CameraNode();
    explicit CameraNode(node_id_t id);
public:
    virtual ~CameraNode();

public:
    virtual void setViewTransform(SceneGraph* scene_graph);
    
    virtual bool isVisible(SceneGraph* scene_graph) const override {
        return active_;
    }
    
    virtual void render(SceneGraph* scene_graph);
    
    static std::shared_ptr<CameraNode> create(
        node_id_t id
    );
    
    
    const Frustum* getFrustom() const {
        return &frustum_;
    }

private:
    void    calculateFrustum();

    void    calculateDirection();

    void    recalculateDirection();


    
    
protected:
    
    bool debug_camera_;
    bool active_;
    
    //  基本パラメータ
    Vec3 position_;   // カメラ座標
    Vec3 target_;     // 注視点
    float fov_;         // 視野角
    float twist_;       // 注視点方向ひねり角

    Vec3 up_;         // 上方向ベクトル
    Vec3 front_;      // 前方向ベクトル
    Vec3 right_;      // 右方向ベクトル

    Mtx4 view_matrix_;
    Frustum frustum_;

};

}   // gfx
}   // t3



#endif
