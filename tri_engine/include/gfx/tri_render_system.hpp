
#ifndef TRI_RENDER_SYSTEM_HPP
#define TRI_RENDER_SYSTEM_HPP

#include "math/tri_matrix.hpp"
#include "gfx/tri_color.hpp"
//#include "gfx/tri_texture.hpp"
#include "platform/platform_sdk.hpp"
#include <memory>

namespace t3 {


inline namespace gfx {


class Texture;

class RenderSystem {
public:

    static void initializeRenderSystem();

    enum class ColorFormat {
        RGB,
        RGBA,
        BGR
    };

    enum class CullingMode {
        MODE_FRONT,     ///< 前面カリング
        MODE_BACK,      ///< 背面カリング
    };
    
    /// ----------------------------------
    /// カリングモードの設定.
    /// 隠面除去の設定を行います
    static void setCullingMode(
        CullingMode mode        ///< モード
    );
    
    
    static void swapBuffers();
    
    static void clearBuffer(
        bool color_clear,
        bool depth_clear,
        bool stencil_clear
    );
    
    
    static void setDepthWrite(
        bool enable     ///< true = 書き込み有効
    );
    
    static void setClearDepthValue(
        const float value
    );
    
    static void setClearColor(
        float r,
        float g,
        float b,
        float a
    );
    
    
    enum class DepthTestMode {
        MODE_NEVER,
        MODE_LESS,
        MODE_ALWAYS
    };
    
    static void setDepthTestMode(
        DepthTestMode mode
    );
    
    enum class BlendFunctionType {
        TYPE_ZERO,
        TYPE_ONE,
        TYPE_SRC_COLOR,
        TYPE_ONE_MINUS_SRC_COLOR,
        TYPE_DST_COLOR,
        TYPE_ONE_MINUS_DST_COLOR,
        TYPE_SRC_ALPHA,
        TYPE_ONE_MINUS_SRC_ALPHA,
        TYPE_DST_ALPHA,
        TYPE_ONE_MINUS_DST_ALPHA,
        TYPE_CONSTANT_COLOR,
        TYPE_ONE_MINUS_CONSTANT_COLOR,
        TYPE_CONSTANT_ALPHA,
        TYPE_ONE_MINUS_CONSTANT_ALPHA,
    };
    
    static void setBlendFunctionType(
        BlendFunctionType sfactor,
        BlendFunctionType dfactor
    );
    
    
    static void setViewport(
        const int x,
        const int y,
        const int w,
        const int h
    );
    
    enum class ShadingType {
        TYPE_FLAT,
        TYPE_SMOOTH
    };
    
    static void setShadingType(
        ShadingType type
    );
    
    static void setDepthTest(
        bool enable
    );
    
    static void setBlend(
        bool enable
    );
    
    static void setCulling(
        bool enable
    );
    
    static void setLighting(
        bool enable
    );
    
    static void setLight0Use(
        bool use
    );
    
    static void setLight1Use(
        bool use
    );
    
    static void setLight2Use(
        bool use
    );
    
    static void setTextureMapping(
        bool enable
    );

    enum class TextureFilterType {
        TYPE_NEAREST,
        TYPE_LINEAR
    };
    static void setTextureMagFilter(
        TextureFilterType type
    );
    
    static void setTextureMinFilter(
        TextureFilterType type
    );
    
    static void setProjectionMatrix(
        const Mtx4& mtx
    );
    
    static void setWorldTransformMatrix(
        const Mtx4& mtx
    );

    enum class DrawMode{
        MODE_TRIANGLES,
        MODE_QUADS,
        MODE_TRIANGLE_STRIP
    };
    static void drawElements(
        DrawMode mode,
        int count,
        size_t indices_type_size
    );
    static void drawQuad(
        const Vec3& p1,
        const Vec3& p2,
        const Vec3& p3,
        const Vec3& p4,
        const Color& color
    );
    
    static void drawQuad(
        const Vec3& p1,
        const Vec3& p2,
        const Vec3& p3,
        const Vec3& p4,
        const Color& color,
        float u0,
        float v0,
        float u1,
        float v1
    );


    static void setVertexPointer(
        int size,
        int stride,
        const void* pointer
    );
    
    static void setNormalPointer(
        int stride,
        const void* normals
    );

    static void setColorPointer(
        int size,
        int stride,
        const void* pointer
    );
    
    static void setTexCoordPointer(
        int size,
        int stride,
        const void* pointer
    );

    static void setTexture(
        const std::shared_ptr<Texture>& texture
    );
    
    
    static void setVertexArrayUse(
        bool use
    );
    static void setColorArrayUse(
        bool use
    );
    static void setTexCoordArrayUse(
        bool use
    );
    static void setNormalArrayUse(
        bool use
    );
    
    
    enum class BufferType {
        TYPE_VERTEX,
        TYPE_INDEX,
    };
    enum class BufferUsage {
        STATIC_DRAW
    };
    static void bindBuffer(
        BufferType target_type,
        int buffer_id
    );
    
    static void createBuffer(uint32_t* buffer);
    
    static void deleteBuffer(uint32_t* buffer);
    
    static void setupBufferData(
        BufferType type,
        int size,
        const void* data,
        BufferUsage usage
    );

    static void setupBufferSubData(
        BufferType type,
        int offset,
        int size,
        const void* data
    );
    
};


}   // namespace gfx
}   // namespace t3













/*

namespace ogl {
    
    
    inline void genBuffers(
        int num,
        uint32_t* buffers
    ){
        glGenBuffers(num, buffers);
    }
    
    inline void deleteBuffers(
        int num,
        uint32_t* buffers
    ) {
        glDeleteBuffers(num, buffers);
    }
    
    inline void bufferData(
        int target,
        int size,
        const void* data,
        int usage
    ) {
        glBufferData(target, size, data, usage);
    }
    
    
    inline void bufferSubData(
        int target,
        int offset,
        int size,
        const void* data
    ) {
        glBufferSubData(
            target,
            offset,
            size,
            data
        );
    }
    
    
}   // namespace ogl;

*/

#endif // TRI_RENDER_SYSTEM_HPP
