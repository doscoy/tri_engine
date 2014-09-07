#include "platform/platform_core_render_system.hpp"
#include "platform/platform_sdk.hpp"
#include "gfx/tri_texture.hpp"



#if defined(PLATFORM_MAC)
extern GLFWwindow* window_;
#endif


#define T3_GL_ASSERT()        checkGLError()

namespace {


inline void checkGLError() {
    int err = glGetError();
    T3_ASSERT_MSG(err == GL_NO_ERROR, "err = %d", err);
}



inline void setGLState(GLenum e, bool f) {
    if (f) {
        glEnable(e);
    }
    else {
        glDisable(e);
    }
    T3_GL_ASSERT();
}


}   // unname namespace


namespace t3 {
inline namespace platform {




void CoreRenderSystem::createFrameBuffer(RenderSystem::FrameBufferID* id) {
    glGenFramebuffers(1, id);
}

void CoreRenderSystem::deleteFrameBuffer(RenderSystem::FrameBufferID* id) {
    glDeleteFramebuffers(1, id);
}

void CoreRenderSystem::bindFrameBuffer(RenderSystem::FrameBufferID id) {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void CoreRenderSystem::createRenderBuffer(RenderSystem::RenderBufferID* id) {
    glGenRenderbuffers(1, id);
}

void CoreRenderSystem::deleteRenderBuffer(RenderSystem::RenderBufferID* id) {
    glDeleteRenderbuffers(1, id);
}

void CoreRenderSystem::bindRenderBuffer(RenderSystem::RenderBufferID id) {
    glBindRenderbuffer(GL_RENDERBUFFER, id);
}


RenderSystem::FrameBufferID CoreRenderSystem::getCurrentFrameBufferID() {
    int id;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &id);
    return id;
}


RenderSystem::RenderBufferID CoreRenderSystem::getCurrentRenderBufferID() {
    int id;
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &id);
    return id;
}


void CoreRenderSystem::bindTexture(RenderSystem::TextureID texture) {

    glBindTexture(GL_TEXTURE_2D, texture);
}

int CoreRenderSystem::buildShader(
    const char* const source,
    RenderSystem::ShaderType shader_type
) {
    int shader_handle = 0;
    
    switch (shader_type) {
        case RenderSystem::ShaderType::VERTEX_SHADER:
            shader_handle = glCreateShader(GL_VERTEX_SHADER);
            break;
            
        case RenderSystem::ShaderType::FRAGMENT_SHADER:
            shader_handle = glCreateShader(GL_FRAGMENT_SHADER);
            break;
            
        case RenderSystem::ShaderType::GEOMETRY_SHADER:
            //            shader_handle = glCreateShader(GL_GEOMETRY_SHADER);
            return -1;
            break;
            
        default:
            return -1;
    }
    
    glShaderSource(shader_handle, 1, &source, 0);
    glCompileShader(shader_handle);
    
    GLint compile_success;
    glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_success);
    
    if (compile_success == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shader_handle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
        return -1;
    }
    
    return shader_handle;
}

void CoreRenderSystem::attachShader(
    RenderSystem::ShaderProgramID program_handle,
    int shader_handle
) {
    glAttachShader(program_handle, shader_handle);
    T3_GL_ASSERT();
}

void CoreRenderSystem::linkShader(
    RenderSystem::ShaderProgramID program_handle
) {
    glLinkProgram(program_handle);
    T3_GL_ASSERT();
}

void CoreRenderSystem::setShader(
    RenderSystem::ShaderProgramID shader
) {
    glUseProgram(shader);
    T3_GL_ASSERT();
}

void CoreRenderSystem::bindAttributeLocation(
    RenderSystem::ShaderProgramID handle,
    RenderSystem::ShaderVariableLocation location,
    const char* const name
) {
    glBindAttribLocation(handle, location, name);
    T3_GL_ASSERT();
}


void CoreRenderSystem::bindFragmentDataLocation(
    RenderSystem::ShaderProgramID handle,
    RenderSystem::ShaderVariableLocation location,
    const char* const name
) {
    //    glBindFragDataLocation();
}

RenderSystem::ShaderVariableLocation CoreRenderSystem::getAttributeLocation(
    RenderSystem::ShaderProgramID program,
    const char* const name
) {
    return glGetAttribLocation(program, name);
}

RenderSystem::ShaderVariableLocation CoreRenderSystem::getUniformLocation(
    RenderSystem::ShaderProgramID program,
    const char* const name
) {
    return glGetUniformLocation(program, name);
}


void CoreRenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    float x,
    float y,
    float z
) {
    glUniform3f(location, x, y, z);
    T3_GL_ASSERT();
}

void CoreRenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    float x,
    float y,
    float z,
    float w
) {
    glUniform4f(location, x, y, z, w);
    T3_GL_ASSERT();
}

void CoreRenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    float val
) {
    glUniform1f(location, val);
    T3_GL_ASSERT();
}

void CoreRenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    int val
) {
    glUniform1i(location, val);
    T3_GL_ASSERT();
}


void CoreRenderSystem::setUniformMatrix(
    RenderSystem::ShaderVariableLocation location,
    t3::Mtx44 mtx
) {
    glUniformMatrix4fv(
        location,
        1,
        0,
        mtx.pointer()
    );
    T3_GL_ASSERT();
}

void CoreRenderSystem::initializeRenderSystem() {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    t3::CoreRenderSystem::setCulling(true);
    
    
}






void CoreRenderSystem::swapBuffers() {
    
#if defined(PLATFORM_MAC)
    glfwSwapBuffers(window_);
#endif
}


void CoreRenderSystem::setDepthWrite(
    bool enable
) {
    glDepthMask(enable);
    T3_GL_ASSERT();
}


void CoreRenderSystem::clearBuffer(
    bool color_clear,
    bool depth_clear,
    bool stencil_clear
) {
    int clear_flag = 0;
    
    if (color_clear) {
        clear_flag |= GL_COLOR_BUFFER_BIT;
    }
    if (depth_clear) {
        clear_flag |= GL_DEPTH_BUFFER_BIT;
    }
    if (stencil_clear) {
        clear_flag |= GL_STENCIL_BUFFER_BIT;
    }
    
    glClear(clear_flag);
    T3_GL_ASSERT();
}

void CoreRenderSystem::setCullingMode(
    RenderSystem::CullingMode mode
) {
    int cull_flag = 0;
    switch (mode) {
        case RenderSystem::CullingMode::MODE_BACK:
            cull_flag = GL_BACK;
            break;
            
        case RenderSystem::CullingMode::MODE_FRONT:
            cull_flag = GL_FRONT;
            break;
            
        default:
            break;
    }
    
    glCullFace(cull_flag);
    T3_GL_ASSERT();
}


void CoreRenderSystem::setClearDepthValue(
    const float value
) {
    glClearDepthf(value);
    T3_GL_ASSERT();
}



void CoreRenderSystem::clearColor(
    float r,
    float g,
    float b,
    float a
) {
    glClearColor(
        r,
        g,
        b,
        a
    );
    T3_GL_ASSERT();
}


void CoreRenderSystem::setDepthTestMode(
    RenderSystem::DepthTestMode mode
) {
    int depth_func = GL_LESS;
    
    switch (mode) {
        case RenderSystem::DepthTestMode::MODE_NEVER:
            depth_func = GL_NEVER;
            break;
            
        case RenderSystem::DepthTestMode::MODE_LESS:
            depth_func = GL_LESS;
            break;
            
        case RenderSystem::DepthTestMode::MODE_ALWAYS:
            depth_func = GL_ALWAYS;
            break;
            
    }
    
    glDepthFunc(depth_func);
    T3_GL_ASSERT();
}


int blendFuncTypeToGLEnum(
    RenderSystem::BlendFunctionType type
) {
    switch (type) {
        case RenderSystem::BlendFunctionType::TYPE_ZERO:
            return GL_ZERO;
            break;
            
        case RenderSystem::BlendFunctionType::TYPE_ONE:
            return GL_ONE;
            break;
            
        case RenderSystem::BlendFunctionType::TYPE_SRC_COLOR:
            return GL_SRC_COLOR;
            break;
            
        case RenderSystem::BlendFunctionType::TYPE_ONE_MINUS_SRC_COLOR:
            return GL_ONE_MINUS_SRC_COLOR;
            break;
            
        case RenderSystem::BlendFunctionType::TYPE_DST_COLOR:
            return GL_DST_COLOR;
            break;
            
        case RenderSystem::BlendFunctionType::TYPE_ONE_MINUS_DST_COLOR:
            return GL_ONE_MINUS_DST_COLOR;
            break;
            
        case RenderSystem::BlendFunctionType::TYPE_SRC_ALPHA:
            return GL_SRC_ALPHA;
            break;
            
        case RenderSystem::BlendFunctionType::TYPE_ONE_MINUS_SRC_ALPHA:
            return GL_ONE_MINUS_SRC_ALPHA;
            break;
            
        case RenderSystem::BlendFunctionType::TYPE_DST_ALPHA:
            return GL_DST_ALPHA;
            break;
            
        case RenderSystem::BlendFunctionType::TYPE_ONE_MINUS_DST_ALPHA:
            return GL_ONE_MINUS_DST_ALPHA;
            break;
            
        case RenderSystem::BlendFunctionType::TYPE_CONSTANT_COLOR:
            return GL_CONSTANT_COLOR;
            break;
            
        case RenderSystem::BlendFunctionType::TYPE_ONE_MINUS_CONSTANT_COLOR:
            return GL_ONE_MINUS_CONSTANT_COLOR;
            break;
            
        case RenderSystem::BlendFunctionType::TYPE_CONSTANT_ALPHA:
            return GL_CONSTANT_ALPHA;
            break;
            
        case RenderSystem::BlendFunctionType::TYPE_ONE_MINUS_CONSTANT_ALPHA:
            return GL_ONE_MINUS_CONSTANT_ALPHA;
            break;
            
        default:
            return GL_ZERO;
            break;
    }
    
}

void CoreRenderSystem::setBlendFunctionType(
    RenderSystem::BlendFunctionType sfactor,
    RenderSystem::BlendFunctionType dfactor
) {
    int s = blendFuncTypeToGLEnum(sfactor);
    int d = blendFuncTypeToGLEnum(dfactor);
    glBlendFunc(s, d);
    T3_GL_ASSERT();
}

void CoreRenderSystem::setViewport(
    const int x,
    const int y,
    const int w,
    const int h
) {
    glViewport(x, y, w, h);
    T3_GL_ASSERT();

}


void CoreRenderSystem::setDepthTest(
    bool enable
) {
    setGLState(GL_DEPTH_TEST, enable);
}

void CoreRenderSystem::setBlend(
    bool enable
) {
    setGLState(GL_BLEND, enable);
}

void CoreRenderSystem::setCulling(
    bool enable
) {
    setGLState(GL_CULL_FACE, enable);
}


void CoreRenderSystem::setTextureMagFilter(
    RenderSystem::TextureFilterType type
) {
    if (type == RenderSystem::TextureFilterType::TYPE_LINEAR) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    T3_GL_ASSERT();
}

void CoreRenderSystem::setTextureMinFilter(
    RenderSystem::TextureFilterType type
) {
    if (type == RenderSystem::TextureFilterType::TYPE_LINEAR) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }
    T3_GL_ASSERT();
}

void CoreRenderSystem::setTextureWrapS(
    RenderSystem::TextureWrapType type
) {
    if (type == RenderSystem::TextureWrapType::TYPE_CLAMP_TO_EDGE) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    }
    else {
        T3_PANIC("unknown type");
    }
    T3_GL_ASSERT();
}

void CoreRenderSystem::setTextureWrapT(
    RenderSystem::TextureWrapType type
) {
    if (type == RenderSystem::TextureWrapType::TYPE_CLAMP_TO_EDGE) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    else {
        T3_PANIC("unknown type");
    }
    T3_GL_ASSERT();
}





void CoreRenderSystem::drawElements(
    RenderSystem::DrawMode mode,
    int count,
    size_t indices_type_size
) {
    //  index_type判定
    int index_type = GL_UNSIGNED_INT;
    switch (indices_type_size) {
        case 1:
            index_type = GL_UNSIGNED_BYTE;
            break;
            
        case 2:
            index_type = GL_UNSIGNED_SHORT;
            break;
            
        case 4:
            index_type = GL_UNSIGNED_INT;
            break;
            
        default:
            T3_PANIC("error");
    }
    
    //  モード判定
    int draw_mode = 0;
    switch (mode) {
        case RenderSystem::DrawMode::MODE_TRIANGLES:
            draw_mode = GL_TRIANGLES;
            break;
            
        case RenderSystem::DrawMode::MODE_TRIANGLE_STRIP:
            draw_mode = GL_TRIANGLE_STRIP;
            break;
            
            
        default:
            T3_PANIC("error");
            break;
    }
    
    glDrawElements(draw_mode, count, index_type, 0);
    T3_GL_ASSERT();
}

void CoreRenderSystem::drawArray(
    RenderSystem::DrawMode mode,
    int first,
    int count
) {
    //  モード判定
    int draw_mode = 0;
    switch (mode) {
        case RenderSystem::DrawMode::MODE_TRIANGLES:
            draw_mode = GL_TRIANGLES;
            break;
            
        case RenderSystem::DrawMode::MODE_TRIANGLE_STRIP:
            draw_mode = GL_TRIANGLE_STRIP;
            break;
            
            
        default:
            T3_PANIC("error");
            break;
    }
    
    glDrawArrays(draw_mode, first, count);
    T3_GL_ASSERT();
}



void CoreRenderSystem::setVertexAttributePointer(
    int slot,
    int element_num,
    int type,
    bool normalized,
    int stride,
    void* ptr
) {
    glVertexAttribPointer(
        slot,
        element_num,
        type,
        normalized,
        stride,
        ptr
    );
}

void CoreRenderSystem::setupTextureData(
    int width,
    int height,
    RenderSystem::ColorFormat color_format,
    const void* data
) {
    int glcolor_format = GL_RGB;
    
    switch (color_format) {
        case RenderSystem::ColorFormat::RGBA:
            glcolor_format = GL_RGBA;
            break;
            
        case RenderSystem::ColorFormat::RGB:
            glcolor_format = GL_RGB;
            break;
            
        case RenderSystem::ColorFormat::BGR:
      //      glcolor_format = GL_BGR;
            break;
            
        default:
            break;
    }
    
    
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        glcolor_format,
        width,
        height,
        0,
        glcolor_format,
        GL_UNSIGNED_BYTE,
        data
    );
    
    T3_GL_ASSERT();
}

void CoreRenderSystem::bindBuffer(
    RenderSystem::BufferType target_type,
    int buffer_id
) {
    int target = GL_ARRAY_BUFFER;
    if (target_type == RenderSystem::BufferType::TYPE_INDEX) {
        target = GL_ELEMENT_ARRAY_BUFFER;
    }
    glBindBuffer(target, buffer_id);
    
    T3_GL_ASSERT();
}


void CoreRenderSystem::createBuffer(uint32_t* buffer) {
    glGenBuffers(1, buffer);
    T3_GL_ASSERT();
}

void CoreRenderSystem::deleteBuffer(uint32_t* buffer) {
    glDeleteBuffers(1, buffer);
    T3_GL_ASSERT();
}

void CoreRenderSystem::setupBufferData(
    RenderSystem::BufferType type,
    int size,
    const void* data,
    RenderSystem::BufferUsage usage
) {
    int target = GL_ARRAY_BUFFER;
    if (type == RenderSystem::BufferType::TYPE_INDEX) {
        target = GL_ELEMENT_ARRAY_BUFFER;
    }
    int gl_usage = GL_STATIC_DRAW;
    if (usage == RenderSystem::BufferUsage::STATIC_DRAW) {
        gl_usage = GL_STATIC_DRAW;
    }
    else if (usage == RenderSystem::BufferUsage::DYNAMIC_DRAW) {
        gl_usage = GL_DYNAMIC_DRAW;
    }
    
    glBufferData(target, size, data, gl_usage);
    T3_GL_ASSERT();
}

void CoreRenderSystem::setupBufferSubData(
    RenderSystem::BufferType type,
    int offset,
    int size,
    const void *data
) {
    int target = GL_ARRAY_BUFFER;
    if (type == RenderSystem::BufferType::TYPE_INDEX) {
        target = GL_ELEMENT_ARRAY_BUFFER;
    }
    
    glBufferSubData(target, offset, size, data);
    T3_GL_ASSERT();
}

void CoreRenderSystem::setActiveTextureUnit(
    int unit
) {
    unit += GL_TEXTURE0;
    glActiveTexture(unit);
    T3_GL_ASSERT();
}

void CoreRenderSystem::setEnableVertexAttribute(
    int slot
) {
    glEnableVertexAttribArray(slot);
    T3_GL_ASSERT();
}

void CoreRenderSystem::setDisableVertexAttribute(
    int slot
) {
    glDisableVertexAttribArray(slot);
    T3_GL_ASSERT();
}

void CoreRenderSystem::setAttributeValue(
    int slot,
    float a,
    float b,
    float c,
    float d
) {
    glVertexAttrib4f(
        slot, a, b, c, d
    );
    T3_GL_ASSERT();
}


void CoreRenderSystem::attachRenderBuffer(
    RenderSystem::RenderBufferAttachType type,
    RenderSystem::RenderBufferID id
) {

    int gltype;
    
    if (type == RenderSystem::RenderBufferAttachType::COLOR0) {
        gltype = GL_COLOR_ATTACHMENT0;
    
    }
    else if (type == RenderSystem::RenderBufferAttachType::DEPTH) {
        gltype = GL_DEPTH_ATTACHMENT;
    }


    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        gltype,
        GL_RENDERBUFFER,
        id
    );
    
}


void CoreRenderSystem::attachFrameBufferTexture(
    RenderSystem::RenderBufferAttachType type,
    RenderSystem::TextureID id
) {
    int gltype;
    
    if (type == RenderSystem::RenderBufferAttachType::COLOR0) {
        gltype = GL_COLOR_ATTACHMENT0;
    
    }
    else if (type == RenderSystem::RenderBufferAttachType::DEPTH) {
        gltype = GL_DEPTH_ATTACHMENT;
    }


    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        gltype,   //  カラーバッファとして設定
        GL_TEXTURE_2D,
        id,
        0
    );
    
}


void CoreRenderSystem::setupRenderBufferStorage(
    RenderSystem::RenderBufferUsage usage,
    int width,
    int height
) {
    int glusage;
    
    if (usage == RenderSystem::RenderBufferUsage::COLOR) {
        glusage = GL_RGBA4;
    
    }
    else if (usage == RenderSystem::RenderBufferUsage::DEPTH) {
        glusage = GL_DEPTH_COMPONENT16;
    }




    glRenderbufferStorage(
        GL_RENDERBUFFER,
        glusage,
        width,
        height
    );
}



}   // namespace gfx
}   // namespace t3

