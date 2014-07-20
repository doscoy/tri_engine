

#include "gfx/tri_render_system.hpp"
#include "platform/platform_core_render_system.hpp"


#define BEFORE_JUDGE_GL     (0)

#define COUNT_RENDER_CALL   (1)


int render_call_count_ = 0;



inline void countRenderCall() {
#if COUNT_RENDER_CALL
    render_call_count_ += 1;
#endif
}

namespace t3 {
inline namespace gfx {


int RenderSystem::getRenderCallCount() {
    return render_call_count_;
}

void RenderSystem::resetRenderCallCount() {
    render_call_count_ = 0;
}


int RenderSystem::buildShader(
    const char* const source,
    RenderSystem::ShaderType shader_type
) {
    countRenderCall();
    return CoreRenderSystem::buildShader(source, shader_type);
}

void RenderSystem::attachShader(
    RenderSystem::shader_program_t program_handle,
    int shader_handle
) {
    countRenderCall();
    CoreRenderSystem::attachShader(program_handle, shader_handle);
}

void RenderSystem::linkShader(
    RenderSystem::shader_program_t program_handle
) {
    countRenderCall();
    CoreRenderSystem::linkShader(program_handle);
}

void RenderSystem::setShader(
    RenderSystem::shader_program_t shader
) {
#if BEFORE_JUDGE_GL
    static bool initialized = false;
    static RenderSystem::shader_program_t last;
    if (initialized && last == shader) {
        return;
    }
    initialized = true;
    last = shader;
#endif
    
    countRenderCall();
    CoreRenderSystem::setShader(shader);
}

void RenderSystem::bindAttributeLocation(
    RenderSystem::shader_program_t handle,
    RenderSystem::shader_variable_t location,
    const char* const name
) {
    countRenderCall();
    CoreRenderSystem::bindAttributeLocation(handle, location, name);
}


void RenderSystem::bindFragmentDataLocation(
    RenderSystem::shader_program_t handle,
    RenderSystem::shader_variable_t location,
    const char* const name
) {
    countRenderCall();
    CoreRenderSystem::bindFragmentDataLocation(handle, location, name);
}

RenderSystem::shader_variable_t RenderSystem::getAttributeLocation(
    RenderSystem::shader_program_t program,
    const char* const name
) {
    countRenderCall();
    return CoreRenderSystem::getAttributeLocation(program, name);
}

RenderSystem::shader_variable_t RenderSystem::getUniformLocation(
    RenderSystem::shader_program_t program,
    const char* const name
) {
    countRenderCall();
    return CoreRenderSystem::getUniformLocation(program, name);
}


void RenderSystem::setUniformValue(
    RenderSystem::shader_variable_t location,
    float x,
    float y,
    float z
) {
    countRenderCall();
    CoreRenderSystem::setUniformValue(location, x, y, z);
}

void RenderSystem::setUniformValue(
    RenderSystem::shader_variable_t location,
    float x,
    float y,
    float z,
    float w
) {
    countRenderCall();
    CoreRenderSystem::setUniformValue(location, x, y, z, w);
}

void RenderSystem::setUniformValue(
    RenderSystem::shader_variable_t location,
    float val
) {
    countRenderCall();
    CoreRenderSystem::setUniformValue(location, val);
}

void RenderSystem::setUniformValue(
    RenderSystem::shader_variable_t location,
    int val
) {
    countRenderCall();
    CoreRenderSystem::setUniformValue(location, val);
}


void RenderSystem::setUniformMatrix(
    RenderSystem::shader_variable_t location,
    t3::Mtx4 mtx
) {
    countRenderCall();
    CoreRenderSystem::setUniformMatrix(location, mtx);

}

void RenderSystem::initializeRenderSystem() {
    countRenderCall();
    CoreRenderSystem::initializeRenderSystem();
}






void RenderSystem::swapBuffers() {
    
    countRenderCall();
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

    countRenderCall();
    CoreRenderSystem::setDepthWrite(enable);
}


void RenderSystem::clearBuffer(
    bool color_clear,
    bool depth_clear,
    bool stencil_clear
) {
    countRenderCall();
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
    countRenderCall();
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
    countRenderCall();
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

    countRenderCall();
    CoreRenderSystem::clearColor(clear_color);
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

    countRenderCall();
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
    countRenderCall();
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

    countRenderCall();
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
    countRenderCall();
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
    countRenderCall();
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
    countRenderCall();
    CoreRenderSystem::setCulling(enable);
}

void RenderSystem::setTextureMapping(
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
    countRenderCall();
    CoreRenderSystem::setTextureMapping(enable);
}

void RenderSystem::setTextureMagFilter(
    RenderSystem::TextureFilterType type
) {
    countRenderCall();
    CoreRenderSystem::setTextureMagFilter(type);
}

void RenderSystem::setTextureMinFilter(
    RenderSystem::TextureFilterType type
) {
    countRenderCall();
    CoreRenderSystem::setTextureMinFilter(type);
}


void RenderSystem::drawElements(
    RenderSystem::DrawMode mode,
    int count,
    size_t indices_type_size
) {

    countRenderCall();
    CoreRenderSystem::drawElements(mode, count, indices_type_size);
}




RenderSystem::buffer_id_t RenderSystem::createVertexBuffer(
    std::vector<float>& vertices
) {
    countRenderCall();
    return CoreRenderSystem::createVertexBuffer(vertices);
}

RenderSystem::buffer_id_t RenderSystem::createIndexBuffer(
    std::vector<uint32_t>& indices
) {
    countRenderCall();
    return CoreRenderSystem::createIndexBuffer(indices);
}


void RenderSystem::setVertexAttributePointer(
    int slot,
    int element_num,
    int stride,
    void* ptr
) {
    countRenderCall();
    CoreRenderSystem::setVertexAttributePointer(slot, element_num, stride, ptr);
}

void RenderSystem::setupTextureData(
    int width,
    int height,
    RenderSystem::ColorFormat color_format,
    const void* data
) {
    countRenderCall();
    CoreRenderSystem::setupTextureData(width, height, color_format, data);
}

void RenderSystem::bindBuffer(
    RenderSystem::BufferType target_type,
    int buffer_id
) {
    countRenderCall();
    CoreRenderSystem::bindBuffer(target_type, buffer_id);
}


void RenderSystem::createBuffer(uint32_t* buffer) {

    countRenderCall();
    CoreRenderSystem::createBuffer(buffer);
}

void RenderSystem::deleteBuffer(uint32_t* buffer) {

    countRenderCall();
    CoreRenderSystem::deleteBuffer(buffer);
}

void RenderSystem::setupBufferData(
    RenderSystem::BufferType type,
    int size,
    const void* data,
    RenderSystem::BufferUsage usage
) {
    countRenderCall();
    CoreRenderSystem::setupBufferData(type, size, data, usage);
}

void RenderSystem::setupBufferSubData(
    RenderSystem::BufferType type,
    int offset,
    int size,
    const void *data
) {
    countRenderCall();
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
    countRenderCall();
    CoreRenderSystem::setActiveTextureUnit(unit);
}

void RenderSystem::setEnableVertexAttribute(
    int slot
) {

    countRenderCall();
    CoreRenderSystem::setEnableVertexAttribute(slot);
}

void RenderSystem::setDisableVertexAttribute(
    int slot
) {

    countRenderCall();
    CoreRenderSystem::setDisableVertexAttribute(slot);
}

void RenderSystem::setAttributeValue(
    int slot,
    float a,
    float b,
    float c,
    float d
) {
    countRenderCall();
    CoreRenderSystem::setAttributeValue(slot, a, b, c, d);
}




}   // namespace gfx
}   // namespace t3

