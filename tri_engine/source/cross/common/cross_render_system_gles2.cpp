#include "cross_render_system.hpp"
#include "cross_dbg.hpp"
#include "cross_os.hpp"
#include <iostream>

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>


CROSS_NS_BEGIN


int render_call_count_ = 0;



namespace  {

int viewport_x_ = -99;
int viewport_y_ = -99;
int viewport_w_ = -99;
int viewport_h_ = -99;

};


inline void countDrawCall() {
#if COUNT_RENDER_CALL
    render_call_count_ += 1;
#endif
}


#define CROSS_GL_ASSERT()        checkGLError(__func__)

namespace {


GLsync fence_ = 0;

inline void checkGLError(const char* str) {
    GLenum e = glGetError();
    switch (e) {
    case GL_NO_ERROR:
        return;
    case GL_INVALID_ENUM:
        printConsole("[GL_INVALID_ENUM]An unacceptable value is specified for an enumerated argument\n");
        break;
    case GL_INVALID_VALUE:
        printConsole("[GL_INVALID_VALUE]A numeric argument is out of range\n");
        break;
    case GL_INVALID_OPERATION:
        printConsole("[GL_INVALID_OPERATION]The specified operation is not allowed in the current state\n");
        break;
    case GL_OUT_OF_MEMORY:
        printConsole("[GL_OUT_OF_MEMORY]There is not enough memory left to execute the command\n");
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        printConsole("[GL_INVALID_FRAMEBUFFER_OPERATION]The specified operation is not allowed current frame buffer\n");
        break;
    default:
        printConsole("An OpenGL error unknown\n");
        break;
    }

    printConsole(str);


    CROSS_PANIC();

}



inline void setGLState(GLenum e, bool f) {
    if (f) {
        glEnable(e);
    }
    else {
        glDisable(e);
    }
    CROSS_GL_ASSERT();
}




inline int bufferTypeToGL(RenderSystem::BufferType type) {
    int gl = GL_ARRAY_BUFFER;
    if (type == RenderSystem::BufferType::TYPE_INDEX) {
        gl = GL_ELEMENT_ARRAY_BUFFER;
    }
    return gl;
}

inline int colorFormatToGLInternalFormat(RenderSystem::ColorFormat format) {


    int glcolor_format = GL_RGB;
    
    switch (format) {
        case RenderSystem::ColorFormat::RGBA:
            glcolor_format = GL_RGBA;
            break;
            
        case RenderSystem::ColorFormat::RGB:
            glcolor_format = GL_RGB;
            break;
            
        case RenderSystem::ColorFormat::DEPTH:
            glcolor_format = GL_DEPTH_COMPONENT16;
            break;

        default:
            CROSS_PANIC();
            break;
    }
    
    return glcolor_format;
}

inline int colorFormatToGLFormat(RenderSystem::ColorFormat format) {


    int glcolor_format = GL_RGB;
    
    switch (format) {
        case RenderSystem::ColorFormat::RGBA:
            glcolor_format = GL_RGBA;
            break;
            
        case RenderSystem::ColorFormat::RGB:
            glcolor_format = GL_RGB;
            break;
            

        case RenderSystem::ColorFormat::DEPTH:
            glcolor_format = GL_DEPTH_COMPONENT16;
            break;

        default:
            break;
    }
    
    return glcolor_format;
}

inline int typeFormatToGL(cross::RenderSystem::TypeFormat format) {
    int gltype_format = GL_FLOAT;
    
    switch (format) {
        case cross::RenderSystem::TypeFormat::UNSIGNED_BYTE:
            gltype_format = GL_UNSIGNED_BYTE;
            break;
            
        case cross::RenderSystem::TypeFormat::INT:
            gltype_format = GL_INT;
            break;

        case cross::RenderSystem::TypeFormat::FLOAT:
            gltype_format = GL_FLOAT;
            break;

        case cross::RenderSystem::TypeFormat::UNSIGNED_SHORT:
            gltype_format = GL_UNSIGNED_SHORT;
            break;

        default:
            break;
    }
    
    return gltype_format;

}



inline int colorFormatToGL(cross::RenderSystem::ColorFormat format) {


    int glcolor_format = GL_RGB;
    
    switch (format) {
        case cross::RenderSystem::ColorFormat::RGBA:
            glcolor_format = GL_RGBA;
            break;
            
        case cross::RenderSystem::ColorFormat::RGB:
            glcolor_format = GL_RGB;
            break;
            
        case cross::RenderSystem::ColorFormat::GRAY:
            glcolor_format = GL_ALPHA;
            break;

        case cross::RenderSystem::ColorFormat::GRAYA:
            glcolor_format = GL_LUMINANCE_ALPHA;
            break;

        case cross::RenderSystem::ColorFormat::DEPTH:
            glcolor_format = GL_DEPTH_COMPONENT;
            break;

            
        default:
            break;
    }
    
    return glcolor_format;
}

}   // unname namespace




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
    
    CROSS_GL_ASSERT();
    CROSS_ASSERT(shader_handle > 0);
    
    glShaderSource(shader_handle, 1, &source, 0);
    glCompileShader(shader_handle);
    
    GLint compile_success;
    glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_success);
    
    if (compile_success == GL_FALSE) {
        GLchar messages[512];
        glGetShaderInfoLog(shader_handle, sizeof(messages), 0, &messages[0]);
        std::cout << "\n\n______ Shader compile fail. LOG _________" << std::endl;
        std::cout << messages << std::endl;
        std::cout << "_________________________________________" << std::endl;
        return -1;
    }
    
    return shader_handle;
}

void RenderSystem::attachShader(
    RenderSystem::ShaderProgramID program_handle,
    int shader_handle
) {
    glAttachShader(program_handle, shader_handle);
    CROSS_GL_ASSERT();
}

void RenderSystem::linkShader(
    RenderSystem::ShaderProgramID program_handle
) {
    glLinkProgram(program_handle);
    CROSS_GL_ASSERT();
}

void RenderSystem::setShader(
    RenderSystem::ShaderProgramID shader
) {
    glUseProgram(shader);
    CROSS_GL_ASSERT();
}

void RenderSystem::bindAttributeLocation(
    RenderSystem::ShaderProgramID handle,
    RenderSystem::ShaderVariableLocation location,
    const char* const name
) {
    glBindAttribLocation(handle, location, name);
    CROSS_GL_ASSERT();
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
    int location = glGetAttribLocation(program, name);
    CROSS_GL_ASSERT();
    return location;
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
    CROSS_GL_ASSERT();
}

void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    float x,
    float y,
    float z,
    float w
) {
    glUniform4f(location, x, y, z, w);
    CROSS_GL_ASSERT();
}

void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    float val
) {
    glUniform1f(location, val);
    CROSS_GL_ASSERT();
}

void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    int val
) {
    glUniform1i(location, val);
    CROSS_GL_ASSERT();
}

void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    size_t size,
    float* val
) {
    glUniform1fv(location, static_cast<GLint>(size), val);
    CROSS_GL_ASSERT();
}

void RenderSystem::setUniformMatrix(
    RenderSystem::ShaderVariableLocation location,
    const float* mtx
) {
    glUniformMatrix4fv(
        location,
        1,
        0,
        mtx
    );
    CROSS_GL_ASSERT();
}







void RenderSystem::setDepthWrite(
    bool enable
) {
    glDepthMask(enable);
    CROSS_GL_ASSERT();
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
    CROSS_GL_ASSERT();
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
    CROSS_GL_ASSERT();
}


void RenderSystem::setClearDepthValue(
    const float value
) {
    glClearDepthf(value);
    CROSS_GL_ASSERT();
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
    CROSS_GL_ASSERT();
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
    CROSS_GL_ASSERT();
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
    CROSS_GL_ASSERT();
}

void RenderSystem::setViewportC(
    const int x,
    const int y,
    const int w,
    const int h
) {
    glViewport(x, y, w, h);
    CROSS_GL_ASSERT();

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
    CROSS_GL_ASSERT();
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
    CROSS_GL_ASSERT();
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
    CROSS_GL_ASSERT();
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
    CROSS_GL_ASSERT();
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
            break;
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
//            CROSS_PANIC("error");
            break;
    }
    
    glDrawElements(draw_mode, count, index_type, 0);
    CROSS_GL_ASSERT();
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
//            CROSS_PANIC("error");
            break;
    }
    
    glDrawArrays(draw_mode, first, count);
    CROSS_GL_ASSERT();
}



void RenderSystem::setVertexAttributePointer(
    int slot,
    int element_num,
    RenderSystem::TypeFormat type,
    bool normalized,
    int stride,
    void* ptr
) {
    auto gltype = typeFormatToGL(type);
    

    glVertexAttribPointer(
        slot,
        element_num,
        gltype,
        normalized,
        stride,
        ptr
    );
}

void RenderSystem::setupTextureData(
    int width,
    int height,
    RenderSystem::ColorFormat color_format,
    RenderSystem::TypeFormat type_format,
    const void* data
) {
    int glcolor_format = colorFormatToGL(color_format);
    int glinternal_format = colorFormatToGLInternalFormat(color_format);
    int gltype_format = typeFormatToGL(type_format);
    CROSS_GL_ASSERT();
    
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        glinternal_format,
        width,
        height,
        0,
        glcolor_format,
        gltype_format,
        data
    );
        
    CROSS_GL_ASSERT();
}




void RenderSystem::bindBuffer(
    RenderSystem::BufferType target_type,
    int buffer_id
) {
    int target = bufferTypeToGL(target_type);
    glBindBuffer(target, buffer_id);
    
    CROSS_GL_ASSERT();
}


void RenderSystem::createBuffer(uint32_t* buffer) {
    glGenBuffers(1, buffer);
    CROSS_GL_ASSERT();
}

void RenderSystem::deleteBufferC(uint32_t* buffer) {
    glDeleteBuffers(1, buffer);
    CROSS_GL_ASSERT();
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
    CROSS_GL_ASSERT();
}

void RenderSystem::setupBufferSubData(
    RenderSystem::BufferType type,
    int offset,
    int size,
    const void *data
) {
    int target = bufferTypeToGL(type);
    
    glBufferSubData(target, offset, size, data);
    CROSS_GL_ASSERT();
}

void RenderSystem::setActiveTextureUnit(
    int unit
) {
    unit += GL_TEXTURE0;
    glActiveTexture(unit);
    CROSS_GL_ASSERT();
}

void RenderSystem::setEnableVertexAttribute(
    int slot
) {
    glEnableVertexAttribArray(slot);
    CROSS_GL_ASSERT();
}

void RenderSystem::setDisableVertexAttribute(
    int slot
) {
    glDisableVertexAttribArray(slot);
    CROSS_GL_ASSERT();
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
    CROSS_GL_ASSERT();
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
    CROSS_GL_ASSERT();

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
    CROSS_GL_ASSERT();
   
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
    CROSS_GL_ASSERT();
}

RenderSystem::BufferID RenderSystem::createVertexArrayObject() {
    RenderSystem::BufferID id;
    glGenVertexArraysOES(1, &id);
    CROSS_GL_ASSERT();
    return id;
}



void RenderSystem::bindVertexArrayObject(const RenderSystem::BufferID id) {
    glBindVertexArrayOES(id);
    CROSS_GL_ASSERT();
}


void RenderSystem::deleteVertexArrayBuffer(const RenderSystem::BufferID id) {
    glDeleteVertexArraysOES(1, &id);
    CROSS_GL_ASSERT();
}

void RenderSystem::fenceDraw() {
    fence_ = glFenceSyncAPPLE(GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE, 0);
    CROSS_GL_ASSERT();
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

    CROSS_GL_ASSERT();
}



void RenderSystem::mapBuffer(RenderSystem::BufferType type, intptr_t offset, size_t size, void* data) {

    int gl_type = bufferTypeToGL(type);
    

    CROSS_GL_ASSERT();
    void* buf_data = glMapBufferRangeEXT(
        gl_type,
        offset,
        size,
        GL_MAP_WRITE_BIT_EXT | GL_MAP_FLUSH_EXPLICIT_BIT_EXT | GL_MAP_UNSYNCHRONIZED_BIT_EXT
    );


    CROSS_GL_ASSERT();

    memcpy(buf_data, data, size);
    glFlushMappedBufferRangeEXT(gl_type, offset, size);

    CROSS_GL_ASSERT();
}

void RenderSystem::unmapBuffer(RenderSystem::BufferType type) {
    glUnmapBufferOES(bufferTypeToGL(type));
    CROSS_GL_ASSERT();
}




void RenderSystem::setBlendMode(
    RenderSystem::BlendMode mode
) {
    if (mode == BlendMode::NONE) {
        setBlend(false);
    } else if (mode == BlendMode::ADD) {
        setBlend(true);
        setBlendFunctionType(
            BlendFunctionType::TYPE_SRC_ALPHA,
            BlendFunctionType::TYPE_ONE
        );
    } else {
        setBlend(true);
        setBlendFunctionType(
            BlendFunctionType::TYPE_SRC_ALPHA,
            BlendFunctionType::TYPE_ONE_MINUS_SRC_ALPHA
        );
    }
    
}


int RenderSystem::getDrawCallCount() {
    return render_call_count_;
}

void RenderSystem::resetDrawCallCount() {
    render_call_count_ = 0;
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

    if (initialized && viewport_x_ == x) {
        if (viewport_y_ == y) {
            if (viewport_w_ == w) {
                if (viewport_h_ == h) {
                    return;
                }
            }
        }
    }
    initialized = true;
#endif
    viewport_x_ = x;
    viewport_y_ = y;
    viewport_w_ = w;
    viewport_h_ = h;

    setViewportC(x, y, w, h);
}


void RenderSystem::getViewport(
    int* x,
    int* y,
    int* w,
    int* h
) {
    *x = viewport_x_;
    *y = viewport_y_;
    *w = viewport_w_;
    *h = viewport_h_;
}

void RenderSystem::setTextureWrap(
    RenderSystem::TextureWrapType type
) {
    setTextureWrapS(type);
    setTextureWrapT(type);
}


void RenderSystem::drawElements(
    RenderSystem::DrawMode mode,
    int count,
    size_t indices_type_size
) {
    countDrawCall();
    drawElementsC(mode, count, indices_type_size);
}

void RenderSystem::drawArray(
    RenderSystem::DrawMode mode,
    int first,
    int count
) {
    countDrawCall();
    drawArrayC(mode, first, count);
}




void RenderSystem::deleteBuffer(uint32_t* buffer) {

    deleteBufferC(buffer);
    *buffer = 0;
}

int RenderSystem::createProgram() {
    return glCreateProgram();
}


RenderSystem::TextureID RenderSystem::createTexture() {
    TextureID tex;
    glGenTextures(1, &tex);
    return tex;
}

void RenderSystem::deleteTexture(
    RenderSystem::TextureID* id
) {
    glDeleteTextures(1, id);
}


bool RenderSystem::isError() {
    return glGetError() != GL_NO_ERROR;
}

void RenderSystem::setDrawBuffer(RenderSystem::DrawBufferTarget target) {

//    glDrawBuffer(GL_NONE);
}

void RenderSystem::setTextureCompareFunc(
    RenderSystem::TextureCompareFunc func
) {
    int gl_func = GL_LEQUAL;
    
    if (func == TextureCompareFunc::LEQUAL) {
        gl_func = GL_LEQUAL;
    } else if (func == TextureCompareFunc::LESS) {
        gl_func = GL_LESS;
    }

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, gl_func);
    CROSS_GL_ASSERT();
}

void RenderSystem::setTextureCompareMode(
    RenderSystem::TextureCompareMode mode
) {
//    int gl_mode = GL_COMPARE_REF_TO_TEXTURE;

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, gl_mode);
    CROSS_GL_ASSERT();
}




void RenderSystem::setTextureBorderColor(
    float r,
    float g,
    float b,
    float a
) {
    GLfloat border[] = {r, g, b, a};
//    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
    CROSS_GL_ASSERT();
}

CROSS_NS_END


