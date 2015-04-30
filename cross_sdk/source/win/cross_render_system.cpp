
#include "cross_render_system.hpp"

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



namespace {



inline void checkGLError() {

    
}





inline int bufferTypeToGL(cross::RenderSystem::BufferType type) {

    return 0;
}

inline int colorFormatToGL(cross::RenderSystem::ColorFormat format) {


    return 0;
}

}   // unname namespace


namespace cross {



void RenderSystem::createFrameBuffer(RenderSystem::FrameBufferID* id) {

}

void RenderSystem::deleteFrameBuffer(RenderSystem::FrameBufferID* id) {

}

void RenderSystem::bindFrameBuffer(RenderSystem::FrameBufferID id) {

}

void RenderSystem::createRenderBuffer(RenderSystem::RenderBufferID* id) {

}

void RenderSystem::deleteRenderBuffer(RenderSystem::RenderBufferID* id) {

}

void RenderSystem::bindRenderBuffer(RenderSystem::RenderBufferID id) {

}


RenderSystem::FrameBufferID RenderSystem::getCurrentFrameBufferID() {

    return 0;
}


RenderSystem::RenderBufferID RenderSystem::getCurrentRenderBufferID() {

    return 0;
}


void RenderSystem::bindTexture(RenderSystem::TextureID texture) {

}

int RenderSystem::buildShader(
    const char* const source,
    RenderSystem::ShaderType shader_type
) {
    
    return 0;
}

void RenderSystem::attachShader(
    RenderSystem::ShaderProgramID program_handle,
    int shader_handle
) {

}

void RenderSystem::linkShader(
    RenderSystem::ShaderProgramID program_handle
) {

}

void RenderSystem::setShader(
    RenderSystem::ShaderProgramID shader
) {

}

void RenderSystem::bindAttributeLocation(
    RenderSystem::ShaderProgramID handle,
    RenderSystem::ShaderVariableLocation location,
    const char* const name
) {

}


void RenderSystem::bindFragmentDataLocation(
    RenderSystem::ShaderProgramID handle,
    RenderSystem::ShaderVariableLocation location,
    const char* const name
) {

}

RenderSystem::ShaderVariableLocation RenderSystem::getAttributeLocation(
    RenderSystem::ShaderProgramID program,
    const char* const name
) {
    return 0;
}

RenderSystem::ShaderVariableLocation RenderSystem::getUniformLocation(
    RenderSystem::ShaderProgramID program,
    const char* const name
) {
    return 0;
}


void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    float x,
    float y,
    float z
) {

}

void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    float x,
    float y,
    float z,
    float w
) {

}

void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    float val
) {

}

void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    int val
) {

}

void RenderSystem::setUniformValue(
    RenderSystem::ShaderVariableLocation location,
    size_t size,
    float* val
) {

}

void RenderSystem::setUniformMatrix(
    RenderSystem::ShaderVariableLocation location,
    const float* mtx
) {

}

void RenderSystem::initializeRenderSystem() {
    

    
    
}






void RenderSystem::swapBuffers() {

}


void RenderSystem::setDepthWrite(
    bool enable
) {

}


void RenderSystem::clearBuffer(
    bool color_clear,
    bool depth_clear,
    bool stencil_clear
) {
 
}

void RenderSystem::setCullingMode(
    RenderSystem::CullingMode mode
) {
   
}


void RenderSystem::setClearDepthValue(
    const float value
) {

}



void RenderSystem::clearColor(
    float r,
    float g,
    float b,
    float a
) {

}


void RenderSystem::setDepthTestMode(
    RenderSystem::DepthTestMode mode
) {

}


int blendFuncTypeToGLEnum(
    RenderSystem::BlendFunctionType type
) {
    return 0;
    
}

void RenderSystem::setBlendFunctionType(
    RenderSystem::BlendFunctionType sfactor,
    RenderSystem::BlendFunctionType dfactor
) {

}

void RenderSystem::setViewportC(
    const int x,
    const int y,
    const int w,
    const int h
) {


}


void RenderSystem::setDepthTest(
    bool enable
) {

}

void RenderSystem::setBlend(
    bool enable
) {

}

void RenderSystem::setCulling(
    bool enable
) {

}


void RenderSystem::setTextureMagFilter(
    RenderSystem::TextureFilterType type
) {

}

void RenderSystem::setTextureMinFilter(
    RenderSystem::TextureFilterType type
) {

}

void RenderSystem::setTextureWrapS(
    RenderSystem::TextureWrapType type
) {

}

void RenderSystem::setTextureWrapT(
    RenderSystem::TextureWrapType type
) {

}





void RenderSystem::drawElementsC(
    RenderSystem::DrawMode mode,
    int count,
    size_t indices_type_size
) {
  

}

void RenderSystem::drawArrayC(
    RenderSystem::DrawMode mode,
    int first,
    int count
) {
 
}



void RenderSystem::setVertexAttributePointer(
    int slot,
    int element_num,
    int type,
    bool normalized,
    int stride,
    void* ptr
) {

}

void RenderSystem::setupTextureData(
    int width,
    int height,
    RenderSystem::ColorFormat color_format,
    const void* data
) {

}




void RenderSystem::bindBuffer(
    RenderSystem::BufferType target_type,
    int buffer_id
) {

}


void RenderSystem::createBuffer(uint32_t* buffer) {

}

void RenderSystem::deleteBufferC(uint32_t* buffer) {

}

void RenderSystem::setupBufferData(
    RenderSystem::BufferType type,
    int size,
    const void* data,
    RenderSystem::BufferUsage usage
) {

}

void RenderSystem::setupBufferSubData(
    RenderSystem::BufferType type,
    int offset,
    int size,
    const void *data
) {

}

void RenderSystem::setActiveTextureUnit(
    int unit
) {

}

void RenderSystem::setEnableVertexAttribute(
    int slot
) {

}

void RenderSystem::setDisableVertexAttribute(
    int slot
) {

}

void RenderSystem::setAttributeValue(
    int slot,
    float a,
    float b,
    float c,
    float d
) {

}


void RenderSystem::attachRenderBuffer(
    RenderSystem::RenderBufferAttachType type,
    RenderSystem::RenderBufferID id
) {


}


void RenderSystem::attachFrameBufferTexture(
    RenderSystem::RenderBufferAttachType type,
    RenderSystem::TextureID id
) {
  
   
}


void RenderSystem::setupRenderBufferStorage(
    RenderSystem::RenderBufferUsage usage,
    int width,
    int height
) {
   
}

RenderSystem::BufferID RenderSystem::createVertexArrayBuffer() {

    return 0;
}



void RenderSystem::bindVertexArrayBuffer(const RenderSystem::BufferID id) {

}


void RenderSystem::deleteVertexArrayBuffer(const RenderSystem::BufferID id) {

}

void RenderSystem::fenceDraw() {

}

void RenderSystem::fenceDrawWaiting() {

}



void RenderSystem::mapBuffer(RenderSystem::BufferType type, intptr_t offset, size_t size, void* data) {

}

void RenderSystem::unmapBuffer(RenderSystem::BufferType type) {

}




void RenderSystem::setBlendMode(
    RenderSystem::BlendMode mode
) {

    
}


int RenderSystem::getDrawCallCount() {
    return 0;
}

void RenderSystem::resetDrawCallCount() {

}




void RenderSystem::setViewport(
    const int x,
    const int y,
    const int w,
    const int h
) {
}


void RenderSystem::getViewport(
    int* x,
    int* y,
    int* w,
    int* h
) {

}

void RenderSystem::setTextureWrap(
    RenderSystem::TextureWrapType type
) {

}


void RenderSystem::drawElements(
    RenderSystem::DrawMode mode,
    int count,
    size_t indices_type_size
) {

}

void RenderSystem::drawArray(
    RenderSystem::DrawMode mode,
    int first,
    int count
) {

}




void RenderSystem::deleteBuffer(uint32_t* buffer) {

}

int RenderSystem::createProgram() {
    return 0;
}


RenderSystem::TextureID RenderSystem::createTexture() {

    return 0;
}

void RenderSystem::deleteTexture(
    RenderSystem::TextureID* id
) {

}


bool RenderSystem::isError() {
    return false;
}

}   // namespace cross



