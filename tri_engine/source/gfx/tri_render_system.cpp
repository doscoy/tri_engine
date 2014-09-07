

#include "gfx/tri_render_system.hpp"
#include "platform/platform_core_render_system.hpp"


#define BEFORE_JUDGE_GL     (0)

#define COUNT_RENDER_CALL   (1)


int render_call_count_ = 0;



inline void countDrawCall() {
#if COUNT_RENDER_CALL
    render_call_count_ += 1;
#endif
}

namespace t3 {
inline namespace gfx {


void RenderSystem::bindTexture(
    const TextureID texture
) {

    CoreRenderSystem::bindTexture(texture);
}

int RenderSystem::getDrawCallCount() {
    return render_call_count_;
}

void RenderSystem::resetDrawCallCount() {
    render_call_count_ = 0;
}


int RenderSystem::buildShader(
    const char* const source,
    RenderSystem::ShaderType shader_type
) {
    return CoreRenderSystem::buildShader(source, shader_type);
}

void RenderSystem::attachShader(
    RenderSystem::ShaderProgramID program_handle,
    int shader_handle
) {
    CoreRenderSystem::attachShader(program_handle, shader_handle);
}

void RenderSystem::linkShader(
    RenderSystem::ShaderProgramID program_handle
) {
    CoreRenderSystem::linkShader(program_handle);
}

void RenderSystem::setShader(
    RenderSystem::ShaderProgramID shader
) {
#if BEFORE_JUDGE_GL
    static bool initialized = false;
    static RenderSystem::ShaderProgramID last;
    if (initialized && last == shader) {
        return;
    }
    initialized = true;
    last = shader;
#endif
    
    CoreRenderSystem::setShader(shader);
}

void RenderSystem::bindAttributeLocation(
    RenderSystem::ShaderProgramID handle,
    RenderSystem::ShaderVariableLocation location,
    const char* const name
) {
    CoreRenderSystem::bindAttributeLocation(handle, location, name);
}


void RenderSystem::bindFragmentDataLocation(
    RenderSystem::ShaderProgramID handle,
    RenderSystem::ShaderVariableLocation location,
    const char* const name
) {
    CoreRenderSystem::bindFragmentDataLocation(handle, location, name);
}

RenderSystem::ShaderVariableLocation RenderSystem::getAttributeLocation(
    RenderSystem::ShaderProgramID program,
    const char* const name
) {
    return CoreRenderSystem::getAttributeLocation(program, name);
}

RenderSystem::ShaderVariableLocation RenderSystem::getUniformLocation(
    RenderSystem::ShaderProgramID program,
    const char* const name
) {
    return CoreRenderSystem::getUniformLocation(program, name);
}


void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    float x,
    float y,
    float z
) {
    CoreRenderSystem::setUniformValue(location, x, y, z);
}

void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    float x,
    float y,
    float z,
    float w
) {
    CoreRenderSystem::setUniformValue(location, x, y, z, w);
}

void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    float val
) {
    CoreRenderSystem::setUniformValue(location, val);
}

void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    int val
) {
    CoreRenderSystem::setUniformValue(location, val);
}


void RenderSystem::setUniformMatrix(
    RenderSystem::ShaderVariableLocation location,
    t3::Mtx44 mtx
) {
    CoreRenderSystem::setUniformMatrix(location, mtx);

}

void RenderSystem::initializeRenderSystem() {
    CoreRenderSystem::initializeRenderSystem();
}






void RenderSystem::swapBuffers() {
    CoreRenderSystem::swapBuffers();
}


void RenderSystem::setDepthWrite(
    bool enable
) {
#if BEFORE_JUDGE_GL
    static bool initialized = false;
    static bool last;
    if (initialized && last == enable) {
        return;
    }
    initialized = true;
    last = enable;
#endif

    CoreRenderSystem::setDepthWrite(enable);
}


void RenderSystem::clearBuffer(
    bool color_clear,
    bool depth_clear,
    bool stencil_clear
) {
    CoreRenderSystem::clearBuffer(color_clear, depth_clear, stencil_clear);
}

void RenderSystem::setCullingMode(
    RenderSystem::CullingMode mode
) {
#if BEFORE_JUDGE_GL
    static bool initialized = false;
    static RenderSystem::CullingMode last;
    if (initialized && last == mode) {
        return;
    }
    initialized = true;
    last = mode;
#endif
    CoreRenderSystem::setCullingMode(mode);
}


void RenderSystem::setClearDepthValue(
    const float value
) {
#if BEFORE_JUDGE_GL
    static bool initialized = false;
    static float last;
    if (initialized && last == value) {
        return;
    }
    initialized = true;
    last = value;
#endif
    CoreRenderSystem::setClearDepthValue(value);
}



void RenderSystem::clearColor(
    const Color& clear_color
) {
#if BEFORE_JUDGE_GL
    static bool initialized = false;
    static Color last;
    if (initialized && last == clear_color) {
        return;
    }
    initialized = true;
    last = clear_color;
#endif

    CoreRenderSystem::clearColor(
        clear_color.redFloat(),
        clear_color.greenFloat(),
        clear_color.blueFloat(),
        clear_color.alphaFloat()
    );
}


void RenderSystem::setDepthTestMode(
    RenderSystem::DepthTestMode mode
) {
#if BEFORE_JUDGE_GL
    static bool initialized = false;
    static RenderSystem::DepthTestMode last;
    if (initialized && last == mode) {
        return;
    }
    initialized = true;
    last = mode;
#endif

    CoreRenderSystem::setDepthTestMode(mode);
}

void RenderSystem::setBlendFunctionType(
    RenderSystem::BlendFunctionType sfactor,
    RenderSystem::BlendFunctionType dfactor
) {
#if BEFORE_JUDGE_GL
    static bool initialized = false;
    static RenderSystem::BlendFunctionType last_sf;
    static RenderSystem::BlendFunctionType last_df;
    if (initialized && last_sf == sfactor) {
        if (last_df == dfactor) {
            return;
        }
    }
    initialized = true;
    last_sf = sfactor;
    last_df = dfactor;
#endif
    CoreRenderSystem::setBlendFunctionType(sfactor, dfactor);
}

void RenderSystem::setViewport(
    const int x,
    const int y,
    const int w,
    const int h
) {
#if BEFORE_JUDGE_GL
    static bool initialized = false;
    static int last_x;
    static int last_y;
    static int last_w;
    static int last_h;

    if (initialized && last_x == x) {
        if (last_y == y) {
            if (last_w == w) {
                if (last_h == h) {
                    return;
                }
            }
        }
    }
    initialized = true;
    last_x = x;
    last_y = y;
    last_w = w;
    last_h = h;
#endif

    CoreRenderSystem::setViewport(x, y, w, h);
}


void RenderSystem::setDepthTest(
    bool enable
) {
#if BEFORE_JUDGE_GL
    static bool initialized = false;
    static bool last;
    if (initialized && last == enable) {
        return;
    }
    initialized = true;
    last = enable;
#endif
    CoreRenderSystem::setDepthTest(enable);
}

void RenderSystem::setBlend(
    bool enable
) {
#if BEFORE_JUDGE_GL
    static bool initialized = false;
    static bool last;
    if (initialized && last == enable) {
        return;
    }
    initialized = true;
    last = enable;
#endif
    CoreRenderSystem::setBlend(enable);
}

void RenderSystem::setCulling(
    bool enable
) {
#if BEFORE_JUDGE_GL
    static bool initialized = false;
    static bool last;
    if (initialized && last == enable) {
        return;
    }
    initialized = true;
    last = enable;
#endif
    CoreRenderSystem::setCulling(enable);
}



void RenderSystem::setTextureMagFilter(
    RenderSystem::TextureFilterType type
) {
    CoreRenderSystem::setTextureMagFilter(type);
}

void RenderSystem::setTextureMinFilter(
    RenderSystem::TextureFilterType type
) {
    CoreRenderSystem::setTextureMinFilter(type);
}

void RenderSystem::setTextureWrap(
    RenderSystem::TextureWrapType type
) {
    CoreRenderSystem::setTextureWrapS(type);
    CoreRenderSystem::setTextureWrapT(type);
}


void RenderSystem::drawElements(
    RenderSystem::DrawMode mode,
    int count,
    size_t indices_type_size
) {
    countDrawCall();
    CoreRenderSystem::drawElements(mode, count, indices_type_size);
}


void RenderSystem::setVertexAttributePointer(
    int slot,
    int element_num,
    int type,
    bool normalized,
    int stride,
    void* ptr
) {
    CoreRenderSystem::setVertexAttributePointer(slot, element_num, type, normalized, stride, ptr);
}

void RenderSystem::setupTextureData(
    int width,
    int height,
    RenderSystem::ColorFormat color_format,
    const void* data
) {
    CoreRenderSystem::setupTextureData(width, height, color_format, data);
}

void RenderSystem::bindBuffer(
    RenderSystem::BufferType target_type,
    int buffer_id
) {
    CoreRenderSystem::bindBuffer(target_type, buffer_id);
}


void RenderSystem::createBuffer(uint32_t* buffer) {

    CoreRenderSystem::createBuffer(buffer);
}

void RenderSystem::deleteBuffer(uint32_t* buffer) {

    CoreRenderSystem::deleteBuffer(buffer);
    *buffer = 0;
}

void RenderSystem::setupBufferData(
    RenderSystem::BufferType type,
    int size,
    const void* data,
    RenderSystem::BufferUsage usage
) {
    CoreRenderSystem::setupBufferData(type, size, data, usage);
}

void RenderSystem::setupBufferSubData(
    RenderSystem::BufferType type,
    int offset,
    int size,
    const void *data
) {
    CoreRenderSystem::setupBufferSubData(type, offset, size, data);
}

void RenderSystem::setActiveTextureUnit(
    int unit
) {
#if BEFORE_JUDGE_GL
    static bool initialized = false;
    static int last;
    if (initialized && last == unit) {
        return;
    }
    initialized = true;
    last = unit;
#endif
    CoreRenderSystem::setActiveTextureUnit(unit);
}

void RenderSystem::setEnableVertexAttribute(
    int slot
) {
    CoreRenderSystem::setEnableVertexAttribute(slot);
}

void RenderSystem::setDisableVertexAttribute(
    int slot
) {

    CoreRenderSystem::setDisableVertexAttribute(slot);
}

void RenderSystem::setAttributeValue(
    int slot,
    float a,
    float b,
    float c,
    float d
) {

    CoreRenderSystem::setAttributeValue(slot, a, b, c, d);
}




}   // namespace gfx
}   // namespace t3

