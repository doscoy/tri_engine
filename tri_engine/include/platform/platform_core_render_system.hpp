
#ifndef PLATFORM_RENDER_SYSTEM_HPP
#define PLATFORM_RENDER_SYSTEM_HPP

#include "math/tri_matrix.hpp"
#include "gfx/tri_color.hpp"
#include "platform/platform_sdk.hpp"
#include "gfx/tri_render_system.hpp"

#include <memory>
#include <vector>


#define STRINGIFY(A)  #A



namespace t3 {



inline namespace platform {


class CoreRenderSystem {
public:

    static void bindTexture(
        RenderSystem::TextureID texture
    );

    static void setActiveTextureUnit(
        int unit
    );

    static int buildShader(
        const char* const source,
        RenderSystem::ShaderType shader_type
    );
    
    static void attachShader(
        RenderSystem::ShaderProgramID program_handle,
        int shader_handle
    );

    static void linkShader(
        RenderSystem::ShaderProgramID
    );
    
    static RenderSystem::ShaderVariableLocation getUniformLocation(
        RenderSystem::ShaderProgramID program,
        const char* const name
    );

    static RenderSystem::ShaderVariableLocation getAttributeLocation(
        RenderSystem::ShaderProgramID program,
        const char* const name
    );

    static void bindAttributeLocation(
        RenderSystem::ShaderProgramID handle,
        RenderSystem::ShaderVariableLocation location,
        const char* const name
    );

    static void bindFragmentDataLocation(
        RenderSystem::ShaderProgramID handle,
        RenderSystem::ShaderVariableLocation location,
        const char* const name
    );

    static void setUniformValue(
        RenderSystem::ShaderVariableLocation location,
        float val
    );
    
    static void setUniformValue(
        RenderSystem::ShaderVariableLocation location,
        int val
    );


    static void setShader(
        RenderSystem::ShaderProgramID shader
    );

    static void setUniformValue(
        RenderSystem::ShaderVariableLocation,
        float x,
        float y,
        float z
    );
    
    static void setUniformValue(
        RenderSystem::ShaderVariableLocation location,
        float x,
        float y,
        float z,
        float w
    );

    static void setUniformMatrix(
        RenderSystem::ShaderVariableLocation location,
        t3::Mtx44 mtx
    );

    static void initializeRenderSystem();

    
    static void setupTextureData(
        int width,
        int height,
        RenderSystem::ColorFormat color_format,
        const void* data
    );


    
    /// ----------------------------------
    /// カリングモードの設定.
    /// 隠面除去の設定を行います
    static void setCullingMode(
        RenderSystem::CullingMode mode        ///< モード
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
        float r,
        float g,
        float b,
        float a
    );
    

    
    static void setDepthTestMode(
        RenderSystem::DepthTestMode mode
    );
    
 
    
    static void setBlendFunctionType(
        RenderSystem::BlendFunctionType sfactor,
        RenderSystem::BlendFunctionType dfactor
    );
    
    
    static void setViewport(
        const int x,
        const int y,
        const int w,
        const int h
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
    


    static void setTextureMagFilter(
        RenderSystem::TextureFilterType type
    );
    
    static void setTextureMinFilter(
        RenderSystem::TextureFilterType type
    );

    static void drawElements(
        RenderSystem::DrawMode mode,
        int count,
        size_t indices_type_size
    );


    static void bindBuffer(
        RenderSystem::BufferType target_type,
        int buffer_id
    );
    
    static void resetBufferBind() {
        bindBuffer(RenderSystem::BufferType::TYPE_VERTEX, 0);
    }
    
    static void createBuffer(uint32_t* buffer);
    
    static void deleteBuffer(uint32_t* buffer);
    
    static void setupBufferData(
        RenderSystem::BufferType type,
        int size,
        const void* data,
        RenderSystem::BufferUsage usage
    );

    static void setupBufferSubData(
        RenderSystem::BufferType type,
        int offset,
        int size,
        const void* data
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
};


}   // namespace gfx
}   // namespace t3


#endif // TRI_RENDER_SYSTEM_HPP
