#include "gfx/tri_render_system.hpp"
#include "platform/platform_sdk.hpp"
#include "gfx/tri_texture.hpp"



#if defined(PLATFORM_MAC)
extern GLFWwindow* window_;
#endif


#define T3_GL_ASSERT()        checkGLError()

namespace {


GLsync fence_ = 0;

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



inline int bufferTypeToGL(t3::RenderSystem::BufferType type) {
    int gl = GL_ARRAY_BUFFER;
    if (type == t3::RenderSystem::BufferType::TYPE_INDEX) {
        gl = GL_ELEMENT_ARRAY_BUFFER;
    }
    return gl;
}

inline int colorFormatToGL(t3::RenderSystem::ColorFormat format) {


    int glcolor_format = GL_RGB;
    
    switch (format) {
        case t3::RenderSystem::ColorFormat::RGBA:
            glcolor_format = GL_RGBA;
            break;
            
        case t3::RenderSystem::ColorFormat::RGB:
            glcolor_format = GL_RGB;
            break;
            
        case t3::RenderSystem::ColorFormat::GRAY:
            glcolor_format = GL_ALPHA;
            break;

        case t3::RenderSystem::ColorFormat::GRAYA:
            glcolor_format = GL_LUMINANCE_ALPHA;
            break;
            
        default:
            T3_PANIC("unknown format");
            break;
    }
    
    return glcolor_format;
}

}   // unname namespace


namespace t3 {
inline namespace gfx {


void RenderSystem::createFrameBuffer(RenderSystem::FrameBufferID* id) {
    glGenFramebuffers(1, id);
}

void RenderSystem::deleteFrameBuffer(RenderSystem::FrameBufferID* id) {
    glDeleteFramebuffers(1, id);
}

void RenderSystem::bindFrameBuffer(RenderSystem::FrameBufferID id) {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void RenderSystem::createRenderBuffer(RenderSystem::RenderBufferID* id) {
    glGenRenderbuffers(1, id);
}

void RenderSystem::deleteRenderBuffer(RenderSystem::RenderBufferID* id) {
    glDeleteRenderbuffers(1, id);
}

void RenderSystem::bindRenderBuffer(RenderSystem::RenderBufferID id) {
    glBindRenderbuffer(GL_RENDERBUFFER, id);
}


RenderSystem::FrameBufferID RenderSystem::getCurrentFrameBufferID() {
    int id;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &id);
    return id;
}


RenderSystem::RenderBufferID RenderSystem::getCurrentRenderBufferID() {
    int id;
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &id);
    return id;
}


void RenderSystem::bindTexture(RenderSystem::TextureID texture) {

    glBindTexture(GL_TEXTURE_2D, texture);
}

int RenderSystem::buildShader(
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

void RenderSystem::attachShader(
    RenderSystem::ShaderProgramID program_handle,
    int shader_handle
) {
    glAttachShader(program_handle, shader_handle);
    T3_GL_ASSERT();
}

void RenderSystem::linkShader(
    RenderSystem::ShaderProgramID program_handle
) {
    glLinkProgram(program_handle);
    T3_GL_ASSERT();
}

void RenderSystem::setShader(
    RenderSystem::ShaderProgramID shader
) {
    glUseProgram(shader);
    T3_GL_ASSERT();
}

void RenderSystem::bindAttributeLocation(
    RenderSystem::ShaderProgramID handle,
    RenderSystem::ShaderVariableLocation location,
    const char* const name
) {
    glBindAttribLocation(handle, location, name);
    T3_GL_ASSERT();
}


void RenderSystem::bindFragmentDataLocation(
    RenderSystem::ShaderProgramID handle,
    RenderSystem::ShaderVariableLocation location,
    const char* const name
) {
    //    glBindFragDataLocation();
}

RenderSystem::ShaderVariableLocation RenderSystem::getAttributeLocation(
    RenderSystem::ShaderProgramID program,
    const char* const name
) {
    return glGetAttribLocation(program, name);
}

RenderSystem::ShaderVariableLocation RenderSystem::getUniformLocation(
    RenderSystem::ShaderProgramID program,
    const char* const name
) {
    return glGetUniformLocation(program, name);
}


void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    float x,
    float y,
    float z
) {
    glUniform3f(location, x, y, z);
    T3_GL_ASSERT();
}

void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    float x,
    float y,
    float z,
    float w
) {
    glUniform4f(location, x, y, z, w);
    T3_GL_ASSERT();
}

void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    float val
) {
    glUniform1f(location, val);
    T3_GL_ASSERT();
}

void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    int val
) {
    glUniform1i(location, val);
    T3_GL_ASSERT();
}

void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    size_t size,
    float* val
) {
    glUniform1fv(location, static_cast<GLint>(size), val);
    T3_GL_ASSERT();
}

void RenderSystem::setUniformMatrix(
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

void RenderSystem::initializeRenderSystem() {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    t3::RenderSystem::setCulling(true);
    
    
}






void RenderSystem::swapBuffers() {
    
#if defined(PLATFORM_MAC)
    glfwSwapBuffers(window_);
#endif
}


void RenderSystem::setDepthWrite(
    bool enable
) {
    glDepthMask(enable);
    T3_GL_ASSERT();
}


void RenderSystem::clearBuffer(
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

void RenderSystem::setCullingMode(
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


void RenderSystem::setClearDepthValue(
    const float value
) {
    glClearDepthf(value);
    T3_GL_ASSERT();
}



void RenderSystem::clearColor(
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


void RenderSystem::setDepthTestMode(
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

void RenderSystem::setBlendFunctionType(
    RenderSystem::BlendFunctionType sfactor,
    RenderSystem::BlendFunctionType dfactor
) {
    int s = blendFuncTypeToGLEnum(sfactor);
    int d = blendFuncTypeToGLEnum(dfactor);
    glBlendFunc(s, d);
    T3_GL_ASSERT();
}

void RenderSystem::setViewportC(
    const int x,
    const int y,
    const int w,
    const int h
) {
    glViewport(x, y, w, h);
    T3_GL_ASSERT();

}


void RenderSystem::setDepthTest(
    bool enable
) {
    setGLState(GL_DEPTH_TEST, enable);
}

void RenderSystem::setBlend(
    bool enable
) {
    setGLState(GL_BLEND, enable);
}

void RenderSystem::setCulling(
    bool enable
) {
    setGLState(GL_CULL_FACE, enable);
}


void RenderSystem::setTextureMagFilter(
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

void RenderSystem::setTextureMinFilter(
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

void RenderSystem::setTextureWrapS(
    RenderSystem::TextureWrapType type
) {
    if (type == RenderSystem::TextureWrapType::CLAMP_TO_EDGE) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    }
    else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    }
    T3_GL_ASSERT();
}

void RenderSystem::setTextureWrapT(
    RenderSystem::TextureWrapType type
) {
    if (type == RenderSystem::TextureWrapType::CLAMP_TO_EDGE) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    T3_GL_ASSERT();
}





void RenderSystem::drawElementsC(
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

void RenderSystem::drawArrayC(
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



void RenderSystem::setVertexAttributePointer(
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

void RenderSystem::setupTextureData(
    int width,
    int height,
    RenderSystem::ColorFormat color_format,
    const void* data
) {
    int glcolor_format = colorFormatToGL(color_format);
    
    
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




void RenderSystem::bindBuffer(
    RenderSystem::BufferType target_type,
    int buffer_id
) {
    int target = bufferTypeToGL(target_type);
    glBindBuffer(target, buffer_id);
    
    T3_GL_ASSERT();
}


void RenderSystem::createBuffer(uint32_t* buffer) {
    glGenBuffers(1, buffer);
    T3_GL_ASSERT();
}

void RenderSystem::deleteBufferC(uint32_t* buffer) {
    glDeleteBuffers(1, buffer);
    T3_GL_ASSERT();
}

void RenderSystem::setupBufferData(
    RenderSystem::BufferType type,
    int size,
    const void* data,
    RenderSystem::BufferUsage usage
) {
    int target = bufferTypeToGL(type);

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

void RenderSystem::setupBufferSubData(
    RenderSystem::BufferType type,
    int offset,
    int size,
    const void *data
) {
    int target = bufferTypeToGL(type);
    
    glBufferSubData(target, offset, size, data);
    T3_GL_ASSERT();
}

void RenderSystem::setActiveTextureUnit(
    int unit
) {
    unit += GL_TEXTURE0;
    glActiveTexture(unit);
    T3_GL_ASSERT();
}

void RenderSystem::setEnableVertexAttribute(
    int slot
) {
    glEnableVertexAttribArray(slot);
    T3_GL_ASSERT();
}

void RenderSystem::setDisableVertexAttribute(
    int slot
) {
    glDisableVertexAttribArray(slot);
    T3_GL_ASSERT();
}

void RenderSystem::setAttributeValue(
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


void RenderSystem::attachRenderBuffer(
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
    T3_GL_ASSERT();

}


void RenderSystem::attachFrameBufferTexture(
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
    T3_GL_ASSERT();
   
}


void RenderSystem::setupRenderBufferStorage(
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
    T3_GL_ASSERT();
}

RenderSystem::BufferID RenderSystem::createVertexArrayBuffer() {
    RenderSystem::BufferID id;
    glGenVertexArraysOES(1, &id);
    T3_GL_ASSERT();
    return id;
}



void RenderSystem::bindVertexArrayBuffer(const RenderSystem::BufferID id) {
    glBindVertexArrayOES(id);
    T3_GL_ASSERT();
}


void RenderSystem::deleteVertexArrayBuffer(const RenderSystem::BufferID id) {
    glDeleteVertexArraysOES(1, &id);
    T3_GL_ASSERT();
}

void RenderSystem::fenceDraw() {
    fence_ = glFenceSyncAPPLE(GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE, 0);
    T3_GL_ASSERT();
}

void RenderSystem::fenceDrawWaiting() {
    if (!fence_) {
        return;
    }
    glClientWaitSyncAPPLE(
        fence_,
        GL_SYNC_FLUSH_COMMANDS_BIT_APPLE,
        GL_TIMEOUT_IGNORED_APPLE
    );

    T3_GL_ASSERT();
}



void RenderSystem::mapBuffer(RenderSystem::BufferType type, intptr_t offset, size_t size, void* data) {

    int gl_type = bufferTypeToGL(type);
    

    T3_GL_ASSERT();
    void* buf_data = glMapBufferRangeEXT(
        gl_type,
        offset,
        size,
        GL_MAP_WRITE_BIT_EXT | GL_MAP_FLUSH_EXPLICIT_BIT_EXT | GL_MAP_UNSYNCHRONIZED_BIT_EXT
    );


    T3_GL_ASSERT();

    memcpy(buf_data, data, size);
    glFlushMappedBufferRangeEXT(gl_type, offset, size);

    T3_GL_ASSERT();
}

void RenderSystem::unmapBuffer(RenderSystem::BufferType type) {
    glUnmapBufferOES(bufferTypeToGL(type));
    T3_GL_ASSERT();
}


}   // namespace gfx
}   // namespace t3

