
#include "tri_draw_primitive.hpp"
#include "platform/platform_sdk.hpp"
#include "platform/platform.hpp"
#include "geometry/tri_geometry.hpp"
#include "base/tri_director.hpp"
#include "gfx/tri_render_system.hpp"
#include "gfx/tri_shader.hpp"

#include "../shader/tri_simple2d.vsh"
#include "../shader/tri_simple2d.fsh"

namespace {


t3::Shader simple2d_;


}   // unname namespace



namespace t3 {
inline namespace dbg {


void initializeDrawPrimitive()
{
    simple2d_.compileShaderFromString(simple2d_vsh, RenderSystem::ShaderType::VERTEX_SHADER);
    simple2d_.compileShaderFromString(simple2d_fsh, RenderSystem::ShaderType::FRAGMENT_SHADER);
    bool shader_link_result = simple2d_.link();
    T3_ASSERT(shader_link_result);

}




void drawPoint(
    const Vec3& pos,
    const Color& color
) {
    Segment seg1(pos - Vec3(1,0,0), pos + Vec3(1,0,0));
    Segment seg2(pos - Vec3(0,0,1), pos + Vec3(0,0,1));
    
    drawSegment(seg1, color, 0.1f);
    drawSegment(seg2, color, 0.1f);
}

    
void drawRectangle(
    const Vec2& min_pos,
    const Vec2& size,
    const Color& color
){
    
    t3::Director& gs = t3::Director::instance();
    
    float screen_width = gs.virtualScreenSize().x_ * 0.5f;
    float screen_height = gs.virtualScreenSize().y_ * 0.5f;
    
    Vec2 view_left_top(
        min_pos.x_ / screen_width,
        min_pos.y_ / screen_height
    );
    
    Vec2 view_right_bottom(
        (min_pos.x_ + size.x_) / screen_width,
        (min_pos.y_ + size.y_) / screen_height
    );
    
    drawRectangleViewport(
        view_left_top,
        view_right_bottom,
        color
    );

}

void drawRectangleViewport(
    const Vec2& left_top,
    const Vec2& right_bottom,
    const Color& color
) {

    //  状態設定
    t3::RenderSystem::resetBufferBind();

    //  頂点配列を作る
    float x0 = left_top.x_;
    float x1 = right_bottom.x_;
    float y0 = left_top.y_;
    float y1 = right_bottom.y_;
    

    float varray[] = {
        x0, y0,
        x0, y1,
        x1, y0,
        x1, y1
    };


    RenderSystem::setBlend(true);
    RenderSystem::setCulling(false);



    //  シェーダ設定
    bool result = simple2d_.use();
    T3_ASSERT(result);
    
    //  描画
    // シェーダで描画
    RenderSystem::ShaderVariableLocation position_slot = simple2d_.getAttributeLocation("in_position");
    t3::RenderSystem::setEnableVertexAttribute(position_slot);
    
    t3::RenderSystem::setVertexAttributePointer(
        position_slot,
        2,
        GL_FLOAT,
        false,
        0,
        varray
    );
    
    
    simple2d_.setUniform(
        "in_color",
        color.redFloat(),
        color.greenFloat(),
        color.blueFloat(),
        color.alphaFloat()
    );
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void drawSegment(
    const Segment& Segment,
    const Color& color,
    const float width
) {
    
    const Vec3* a = Segment.getPointA();
    const Vec3* b = Segment.getPointB();
    
    Vec3 ba = *b - *a;
    Vec3 cross(0,1,0);
    if (isZeroFloat(ba.x_) && isZeroFloat(ba.z_)) {
        //  完全に垂直
        cross = Vec3(1,0,0);
    }

    Vec3 offset = ba.crossProduct(cross);
    offset.normalize();
    
    offset *= width;
//    Vec3 c = *a + offset;
//    Vec3 d = *b + offset;
    
}

void drawAxis(
    const Vec3& pos
) {
        t3::Segment seg1(
        t3::Vec3(0, 3, 0),
        t3::Vec3(0, 0, 0)
    );

    t3::Segment seg2(
        t3::Vec3(0, 0, 3),
        t3::Vec3(0, 0, 0)
    );

    t3::Segment seg3(
        t3::Vec3(3, 0, 0),
        t3::Vec3(0, 0, 0)
    );
    
    t3::drawSegment(seg1, t3::Color::red(), 3.1f);
    t3::drawSegment(seg2, t3::Color::blue(), 3.1f);
    t3::drawSegment(seg3, t3::Color::green(), 3.1f);
}

void drawPlane(
    const Vec3& center,
    const Vec3& normal,
    const Vec3& size,
    const Color& color
){

}


}   // inline namespace dbg
}   // namespace t3
