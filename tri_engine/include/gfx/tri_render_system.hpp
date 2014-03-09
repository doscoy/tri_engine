
#ifndef TRI_RENDER_SYSTEM_HPP
#define TRI_RENDER_SYSTEM_HPP

#include "math/tri_matrix.hpp"
#include "gfx/tri_color.hpp"
#include "platform/platform_sdk.hpp"

#include <memory>
#include <vector>


#define STRINGIFY(A)  #A



namespace t3 {


inline namespace gfx {

using buffer_id_t = unsigned int;
using shader_program_t = unsigned int;
using shader_variable_t = unsigned int;


class Texture;

class RenderSystem {
public:

    enum TextureUnit {
        UNIT0 = 0,
        UNIT1 = 1,
        UNIT2 = 2,
        UNIT3 = 3,
        UNIT4 = 4
    };
    
    static void setActiveTextureUnit(
        int unit
    );



    enum class ShaderType {
        VERTEX_SHADER,
        FRAGMENT_SHADER,
        GEOMETRY_SHADER
    };

    static int buildShader(
        const char* const source,
        ShaderType shader_type
    );
    
    static void attachShader(
        shader_program_t program_handle,
        int shader_handle
    );

    static void linkShader(
        shader_program_t
    );
    
    static shader_variable_t getUniformLocation(
        shader_program_t program,
        const char* const name
    );

    static shader_variable_t getAttributeLocation(
        shader_program_t program,
        const char* const name
    );

    static void bindAttributeLocation(
        shader_program_t handle,
        shader_variable_t location,
        const char* const name
    );

    static void bindFragmentDataLocation(
        shader_program_t handle,
        shader_variable_t location,
        const char* const name
    );

    static void setUniformValue(
        shader_variable_t location,
        float val
    );
    
    static void setUniformValue(
        shader_variable_t location,
        int val
    );


    static void setShader(
        shader_program_t shader
    );

    static void setUniformValue(
        shader_variable_t,
        float x,
        float y,
        float z
    );

    static void setUniformMatrix(
        shader_variable_t location,
        t3::Mtx4 mtx
    );

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
       const Color& clear_color
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
    
    
    static buffer_id_t createVertexBuffer(
        std::vector<float>& vertices
    );
    
    static buffer_id_t createIndexBuffer(
        std::vector<uint32_t>& indices
    );
  
    
    static void setVertexAttribute(
        int attribute_id,
        int size,
        int stride,
        int offset
    );
};


}   // namespace gfx
}   // namespace t3


#endif // TRI_RENDER_SYSTEM_HPP
