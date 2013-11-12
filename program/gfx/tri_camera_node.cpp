
#include "tri_camera_node.hpp"
#include "tri_scene_graph.hpp"
#include "../base/tri_game_system.hpp"


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
    , position_(0, 20, 20)
    , target_(0, 0, 0)
    , fov_(toRadian(35.0f))
    , aspect_(800/600)
    , near_(1)
    , far_(10000)
    , twist_(0.0f)
    , up_(0, 1, 0)
    , front_(0, 0, -1)
    , right_(1, 0, 0)
    , recalculation_request_(true)
    , re_frustum_(true)
    , re_matrix_(true)
{
    
}


CameraNode::~CameraNode()
{}

void CameraNode::setViewTransform(
    SceneGraph* scene_graph
) {
    const t3::GameSystem& game_sys = t3::GameSystem::getInstance();
    const t3::Vec2& screen = game_sys.getScreenSize();
    

    ogl::viewport(
        0,
        0,
        screen.x_,
        screen.y_
    );  //ビューポートの設定
    
    ogl::matrixMode(
        GL_PROJECTION
    );
    t3::Mtx4 projection;
    projection.frustum(
        -1,
        1,
        -(float)screen.y_ /screen.x_,
        (float)screen.y_/screen.x_,
        1,
        100
    );
    ogl::loadMatrixf( projection.pointer() );
  
    const Mtx4* view_mtx = getViewMatrix();
    scene_graph->pushAndSetMatrix(*view_mtx);
}

void CameraNode::render(SceneGraph* scene_graph)
{
    if (debug_camera_) {
//        camera_.getFrustom();
    }
}





//-----------------------------------------------------------------------------
void CameraNode::calculateDirection()
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
void CameraNode::recalculateDirection()
{
    if ( recalculation_request_ ){
        //  各方向ベクトルを再計算
        calculateDirection();
        recalculation_request_ = false;
    }
}


const Mtx4* CameraNode::getViewMatrix()
{
    if (re_matrix_) {
        re_matrix_ = false;
        view_matrix_.lookat(
            position_,
            target_,
            up_
        );
    }
    
    return &view_matrix_;
}

const Frustum* CameraNode::getFrustum()
{
    if (re_frustum_) {
        re_frustum_ = false;
        frustum_.initializeFrustum(
            fov_,
            aspect_,
            near_,
            far_,
            front_,
            right_,
            up_,
            position_
        );
    }
    return &frustum_;
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