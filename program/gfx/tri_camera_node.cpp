
#include "tri_camera_node.hpp"
#include "tri_scene_graph.hpp"

namespace t3 {
inline namespace gfx {

CameraNode::CameraNode(node_id_t id)
    : SceneNode(
        id,
        "Camera",
        RENDER_PASS_0,
        nullptr
    )
    , debug_camera_(false)
    , active_(true)
{
    
}


CameraNode::~CameraNode()
{}

void CameraNode::setViewTransform(
    SceneGraph* scene_graph
) {
    
}

void CameraNode::render(SceneGraph* scene_graph)
{
    if (debug_camera_) {
        camera_.getFrustom();
    }
}



//-----------------------------------------------------------------------------
void
Camera::calculateDirection()
{

    //  右方向ベクトル計算
    front_ = target_ - position_;
    if ( !isZeroFloat( front_.x_ ) || !isZeroFloat( front_.z_ ) ){
        const Vec3 axis_y( 0, 1, 0 );
        Vec3::getCrossProduct( right_, front_, axis_y );
    }
    else {
        const Vec3 axis_z( 0, 0, 1 );
        Vec3::getCrossProduct( right_, front_, axis_z );
    }

    //  回転を反映
    if ( !isZeroFloat( twist_ ) ){
//        mtx44_t rotate;
//        nn::math::MTX44RotAxisRad_( &rotate, &front_, twist_ );
//        nn::math::VEC3TransformCoord( &right_, &rotate, &right_ );
    }
    right_.normalize();

    //  上方向ベクトル計算
    Vec3::getCrossProduct( up_, right_, front_ );
    up_.normalize();

    //  前方向ベクトル計算
    front_.normalize();
}

//-----------------------------------------------------------------------------
void
Camera::recalculateDirection()
{
    if ( recalculation_request_ ){
        //  各方向ベクトルを再計算
        calculateDirection();
        recalculation_request_ = false;
    }
}


std::shared_ptr<CameraNode> CameraNode::create(
    node_id_t id
) {
    std::shared_ptr<CameraNode> node;
    node.reset(new CameraNode(id));
    return node;
}



}   // namespace gfx
}   // namespace t3