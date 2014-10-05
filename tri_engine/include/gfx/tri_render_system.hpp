
#ifndef TRI_RENDER_SYSTEM_HPP
#define TRI_RENDER_SYSTEM_HPP

#include "math/tri_matrix.hpp"
#include "gfx/tri_color.hpp"
#include "platform/platform_sdk.hpp"
#include "base/tri_std.hpp"


#define TRI_INSTANT_SHADER(A)  #A



namespace t3 {
inline namespace gfx {


class Texture;

class RenderSystem {
public:
    
    using FrameBufferID = unsigned int;
    static void createFrameBuffer(FrameBufferID* id);
    static void deleteFrameBuffer(FrameBufferID* id);
    static void bindFrameBuffer(FrameBufferID id);
    static FrameBufferID getCurrentFrameBufferID();
    
    
    using RenderBufferID = unsigned int;
    static void createRenderBuffer(RenderBufferID* id);
    static void deleteRenderBuffer(RenderBufferID* id);
    static void bindRenderBuffer(RenderBufferID id);
    static RenderBufferID getCurrentRenderBufferID();



    static int getDrawCallCount();
    
    static void resetDrawCallCount();

    using BufferID = unsigned int;
    using ShaderProgramID = unsigned int;
    using ShaderVariableLocation = unsigned int;
    using TextureID = unsigned int;




    enum class BlendMode
        : uint8_t {
        NONE,
        NORMAL,
        ADD
    };

    static void setBlendMode(
        BlendMode mode
    );


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


    static void bindTexture(
        TextureID texture
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
        ShaderProgramID program_handle,
        int shader_handle
    );

    static void linkShader(
        ShaderProgramID
    );
    
    static ShaderVariableLocation getUniformLocation(
        ShaderProgramID program,
        const char* const name
    );

    static ShaderVariableLocation getAttributeLocation(
        ShaderProgramID program,
        const char* const name
    );

    static void bindAttributeLocation(
        ShaderProgramID handle,
        ShaderVariableLocation location,
        const char* const name
    );

    static void bindFragmentDataLocation(
        ShaderProgramID handle,
        ShaderVariableLocation location,
        const char* const name
    );

    static void setUniformValue(
        ShaderVariableLocation location,
        float val
    );
    
    static void setUniformValue(
        ShaderVariableLocation location,
        size_t size,
        float* val
    );
    
    static void setUniformValue(
        ShaderVariableLocation location,
        int val
    );


    static void setShader(
        ShaderProgramID shader
    );

    static void setUniformValue(
        ShaderVariableLocation,
        float x,
        float y,
        float z
    );
    
    static void setUniformValue(
        ShaderVariableLocation location,
        float x,
        float y,
        float z,
        float w
    );

    static void setUniformMatrix(
        ShaderVariableLocation location,
        t3::Mtx44 mtx
    );

    static void initializeRenderSystem();

    enum class ColorFormat {
        RGB,
        RGBA,
        BGR
    };
    
    static void setupTextureData(
        int width,
        int height,
        RenderSystem::ColorFormat color_format,
        const void* data
    );

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
    
    static void clearColor(
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
    
    static void getViewport(
        int* x,
        int* y,
        int* w,
        int* h
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
    
    enum class TextureWrapType {
        TYPE_CLAMP_TO_EDGE,
    };
    
    static void setTextureWrap(
        TextureWrapType s
    );

    enum class DrawMode{
        MODE_TRIANGLES,
        MODE_TRIANGLE_STRIP
    };
    static void drawElements(
        DrawMode mode,
        int count,
        size_t indices_type_size
    );
    
    static void drawArray(
        DrawMode mode,
        int first,
        int count
    );

    enum class BufferType {
        TYPE_VERTEX,
        TYPE_INDEX,
    };
    enum class BufferUsage {
        STATIC_DRAW,
        DYNAMIC_DRAW
    };
    static void bindBuffer(
        BufferType target_type,
        int buffer_id
    );
    
    static void resetBufferBind() {
        bindBuffer(BufferType::TYPE_VERTEX, 0);
        bindBuffer(BufferType::TYPE_INDEX, 0);
    }
    
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
    
    
    static BufferID createVertexBuffer(
        Vector<float>& vertices
    );
    
    static BufferID createIndexBuffer(
        Vector<uint32_t>& indices
    );
  
    
    static void setEnableVertexAttribute(
        int slot
    );
    
    static void setDisableVertexAttribute(
        int slot
    );
    
    static void setVertexAttributePointer(
        int slot,
        int element_num,
        int type,
        bool normalized,
        int stride,
        void* ptr
    );
    
    static void setAttributeValue(
        int slot,
        float a,
        float b,
        float c,
        float d
    );
    
    
    enum class RenderBufferAttachType {
        DEPTH,
        COLOR0,
    };
    
    static void attachRenderBuffer(
        RenderBufferAttachType type,
        RenderBufferID id
    );
    
    static void attachFrameBufferTexture(
        RenderBufferAttachType type,
        TextureID id
    );
    
    enum class RenderBufferUsage {
        DEPTH,
        COLOR,
    };
    
    static void setupRenderBufferStorage(
        RenderBufferUsage usage,
        int width,
        int height
    );
    
    
};


}   // namespace gfx
}   // namespace t3


#endif // TRI_RENDER_SYSTEM_HPP
