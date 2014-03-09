#include "gfx/tri_render_system.hpp"
#include "platform/platform_sdk.hpp"
#include "gfx/tri_texture.hpp"




#include "../shader/tri_simple.vsh"
#include "../shader/tri_simple.fsh"

#if defined(PLATFORM_MAC)
    extern GLFWwindow* window_;
#endif


namespace {
    


    
    
}   // unname namespace


namespace t3 {
inline namespace gfx {


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
        exit(1);
    }
    
    return shader_handle;
}

void RenderSystem::attachShader(
    shader_program_t program_handle,
    int shader_handle
) {
    glAttachShader(program_handle, shader_handle);
}

void RenderSystem::linkShader(
    shader_program_t program_handle
) {
   glLinkProgram(program_handle);
}

void RenderSystem::setShader(
    shader_program_t shader
) {
    glUseProgram(shader);
}

void RenderSystem::bindAttributeLocation(
    shader_program_t handle,
    shader_variable_t location,
    const char* const name
) {
    glBindAttribLocation(handle, location, name);
}


void RenderSystem::bindFragmentDataLocation(
    shader_program_t handle,
    shader_variable_t location,
    const char* const name
) {
//    glBindFragDataLocation();
}

shader_variable_t RenderSystem::getAttributeLocation(
    shader_program_t program,
    const char* const name
) {
    return glGetAttribLocation(program, name);
}

shader_variable_t RenderSystem::getUniformLocation(
    shader_program_t program,
    const char* const name
) {
    return glGetUniformLocation(program, name);
}


void RenderSystem::setUniformValue(
    shader_variable_t location,
    float x,
    float y,
    float z
) {
    glUniform3f(location, x, y, z);
}

void RenderSystem::setUniformValue(
    shader_variable_t location,
    float val
) {
    glUniform1f(location, val);
}

void RenderSystem::setUniformValue(
    shader_variable_t location,
    int val
) {
    glUniform1i(location, val);
}


void RenderSystem::setUniformMatrix(
    shader_variable_t location,
    t3::Mtx4 mtx
) {
    glUniformMatrix4fv(
        location,
        1,
        0,
        mtx.pointer()
    );
    
}

void RenderSystem::initializeRenderSystem() {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    
//    shader_program_t program = buildProgram(SimpleVertexShader, SimpleFragmentShader);
//    glUseProgram(program);
    
    
    // attribute変数とuniform変数のハンドルを取り出す
//    attributes_.position_ = glGetAttribLocation(program, "Position");
//    attributes_.normal_ = glGetAttribLocation(program, "Normal");
//    attributes_.diffuse_ = glGetAttribLocation(program, "DiffuseMaterial");
    
    /*
     uniforms_.Projection = glGetUniformLocation(program, "Projection");
     uniforms_.Modelview = glGetUniformLocation(program, "Modelview");
     uniforms_.NormalMatrix = glGetUniformLocation(program, "NormalMatrix");
     uniforms_.LightPosition = glGetUniformLocation(program, "LightPosition");
     uniforms_.AmbientMaterial = glGetUniformLocation(program, "AmbientMaterial");
     uniforms_.SpecularMaterial = glGetUniformLocation(program, "SpecularMaterial");
     uniforms_.Shininess = glGetUniformLocation(program, "Shininess");
     
     // マテリアルのデフォルトパラメータを設定する
     glUniform3f(uniforms_.AmbientMaterial, 0.04f, 0.04f, 0.04f);
     glUniform3f(uniforms_.SpecularMaterial, 0.5, 0.5, 0.5);
     glUniform1f(uniforms_.Shininess, 50);
     */
    
    
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
}

void RenderSystem::setCullingMode(
    RenderSystem::CullingMode mode
) {
    int cull_flag = 0;
    switch (mode) {
        case CullingMode::MODE_BACK:
            cull_flag = GL_BACK;
            break;
        
        case CullingMode::MODE_FRONT:
            cull_flag = GL_FRONT;
            break;
            
        default:
            break;
    }
    
    glCullFace(cull_flag);
}


void RenderSystem::setClearDepthValue(
    const float value
) {
    glClearDepth(value);
}



void RenderSystem::setClearColor(
    const Color& clear_color
) {
    glClearColor(
        clear_color.redf(),
        clear_color.greenf(),
        clear_color.bluef(),
        clear_color.alphaf()
    );
}


void RenderSystem::setDepthTestMode(
    RenderSystem::DepthTestMode mode
) {
    int depth_func = GL_LESS;

    switch (mode) {
        case DepthTestMode::MODE_NEVER:
            depth_func = GL_NEVER;
            break;
            
        case DepthTestMode::MODE_LESS:
            depth_func = GL_LESS;
            break;
            
        case DepthTestMode::MODE_ALWAYS:
            depth_func = GL_ALWAYS;
            break;
            
    }
    
    glDepthFunc(depth_func);
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
}
    
void RenderSystem::setViewport(
    const int x,
    const int y,
    const int w,
    const int h
) {
    glViewport(x, y, w, h);
}

void RenderSystem::setShadingType(
    t3::RenderSystem::ShadingType type
) {
    if (type == RenderSystem::ShadingType::TYPE_FLAT) {
        glShadeModel(GL_FLAT);
    }
    else {
        glShadeModel(GL_SMOOTH);
    }
}


void RenderSystem::setDepthTest(
    bool enable
) {
    if (enable) {
        glEnable(GL_DEPTH_TEST);
    }
    else {
        glDisable(GL_DEPTH_TEST);
    }
}

void RenderSystem::setBlend(
    bool enable
) {
    if (enable) {
        glEnable(GL_BLEND);
    }
    else {
        glDisable(GL_BLEND);
    }
}

void RenderSystem::setCulling(
    bool enable
) {
    if (enable) {
        glEnable(GL_CULL_FACE);
    }
    else {
        glDisable(GL_CULL_FACE);
    }
}

void RenderSystem::setTextureMapping(
    bool enable
) {
    if (enable) {
        glEnable(GL_TEXTURE_2D);
    }
    else {
        glDisable(GL_TEXTURE_2D);
    }
}

void RenderSystem::setTextureMagFilter(
    t3::RenderSystem::TextureFilterType type
) {
    if (type == RenderSystem::TextureFilterType::TYPE_LINEAR) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
}

void RenderSystem::setTextureMinFilter(
    t3::RenderSystem::TextureFilterType type
) {
    if (type == RenderSystem::TextureFilterType::TYPE_LINEAR) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }
}



void RenderSystem::setProjectionMatrix(
    const Mtx4& mtx
) {

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(mtx.pointer());
}

void RenderSystem::setWorldTransformMatrix(
    const Mtx4& mtx
) {
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(mtx.pointer());
}

void RenderSystem::drawElements(
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

        case RenderSystem::DrawMode::MODE_QUADS:
            draw_mode = GL_QUADS;
            break;
            
        default:
            break;
    }
    
    glDrawElements(draw_mode, count, index_type, 0);
}

void RenderSystem::drawQuad(
    const Vec3& p1,
    const Vec3& p2,
    const Vec3& p3,
    const Vec3& p4,
    const Color& color
) {
    
    glBegin(GL_QUADS);
    
    //  左上
    glColor4ub(color.red_, color.green_, color.blue_, color.alpha_);
    glVertex3f(p1.x_, p1.y_, p1.z_);
    
    //  左下w
    glColor4ub(color.red_, color.green_, color.blue_, color.alpha_);
    glVertex3f(p2.x_, p2.y_, p2.z_);
    
    //  右下
    glColor4ub(color.red_, color.green_, color.blue_, color.alpha_);
    glVertex3f(p3.x_, p3.y_, p3.z_);
    
    //  右上
    glColor4ub(color.red_, color.green_, color.blue_, color.alpha_);
    glVertex3f(p4.x_, p4.y_, p4.z_);
    
    glEnd();
}


void RenderSystem::drawQuad(
    const Vec3& p1,
    const Vec3& p2,
    const Vec3& p3,
    const Vec3& p4,
    const Color& color,
    float u0,
    float v0,
    float u1,
    float v1
) {
    glBegin(GL_QUADS);
    
    //  左上
    glColor4ub(color.red_, color.green_, color.blue_, color.alpha_);
    glTexCoord2f(u0, v0);
    glVertex3f(p1.x_, p1.y_, p1.z_);
    
    //  左下w
    glColor4ub(color.red_, color.green_, color.blue_, color.alpha_);
    glTexCoord2f(u0, v1);
    glVertex3f(p2.x_, p2.y_, p2.z_);
    
    //  右下
    glColor4ub(color.red_, color.green_, color.blue_, color.alpha_);
    glTexCoord2f(u1, v1);
    glVertex3f(p3.x_, p3.y_, p3.z_);
    
    //  右上
    glColor4ub(color.red_, color.green_, color.blue_, color.alpha_);
    glTexCoord2f(u1, v0);
    glVertex3f(p4.x_, p4.y_, p4.z_);
    
    glEnd();
}


    
    
    buffer_id_t RenderSystem::createVertexBuffer(
                                                 std::vector<float>& vertices
                                                 ) {
        
        buffer_id_t buffer_id;
        glGenBuffers(1, &buffer_id);
        glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
        glBufferData(
                     GL_ARRAY_BUFFER,
                     vertices.size() * sizeof(vertices[0]),
                     &vertices[0],
                     GL_STATIC_DRAW
                     );
        
        return buffer_id;
    }
    
    buffer_id_t RenderSystem::createIndexBuffer(
                                                std::vector<uint32_t>& indices
                                                ) {
        buffer_id_t buffer_id;
        
        glGenBuffers(1, &buffer_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indices.size() * sizeof(uint32_t),
                     &indices[0],
                     GL_STATIC_DRAW
                     );
        
        return buffer_id;
    }
    
    
    void RenderSystem::setVertexAttribute(
                                          int attribute_id,
                                          int size,
                                          int stride,
                                          int offset
                                          ) {
        glVertexAttribPointer(
                              attribute_id,
                              size,
                              GL_FLOAT,
                              GL_FALSE,
                              stride,
                              reinterpret_cast<const GLvoid*>(offset)
                              );
    }




void RenderSystem::setVertexPointer(
    int size,
    int stride,
    const void* pointer
) {
    glVertexPointer(size, GL_FLOAT, stride, pointer);
}

void RenderSystem::setNormalPointer(
    int stride,
    const void* pointer
) {
    glNormalPointer(GL_FLOAT, stride, pointer);
}

void RenderSystem::setTexCoordPointer(
    int size,
    int stride,
    const void* pointer
) {
    glTexCoordPointer(size, GL_FLOAT, stride, pointer);
}

void RenderSystem::setColorPointer(
    int size,
    int stride,
    const void* pointer
) {
    glColorPointer(size, GL_UNSIGNED_BYTE, stride, pointer);
}


void RenderSystem::setTexture(
    const std::shared_ptr<Texture>& texture
) {

    int color_format = GL_RGB;
    
    switch (texture->getColorFormat()) {
        case RenderSystem::ColorFormat::RGBA:
            color_format = GL_RGBA;
            break;
            
        case RenderSystem::ColorFormat::RGB:
            color_format = GL_RGB;
            break;
        
        case RenderSystem::ColorFormat::BGR:
            color_format = GL_BGR;
            break;
            
        default:
            break;
    }


    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        color_format,
        texture->getWidth(),
        texture->getHeight(),
        0,
        color_format,
        GL_UNSIGNED_BYTE,
        texture->getData()
    );

}

void RenderSystem::setVertexArrayUse(bool use) {
    if (use) {
        glEnableClientState(GL_VERTEX_ARRAY);
    }
    else {
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

void RenderSystem::setColorArrayUse(bool use) {
    if (use) {
        glEnableClientState(GL_COLOR_ARRAY);
    }
    else {
        glDisableClientState(GL_COLOR_ARRAY);
    }
}

void RenderSystem::setTexCoordArrayUse(bool use) {
    if (use) {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    else {
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
}

void RenderSystem::setNormalArrayUse(bool use) {
    if (use) {
        glEnableClientState(GL_NORMAL_ARRAY);
    }
    else {
        glDisableClientState(GL_NORMAL_ARRAY);
    }
}

void RenderSystem::bindBuffer(
    t3::RenderSystem::BufferType target_type,
    int buffer_id
) {
    int target = GL_ARRAY_BUFFER;
    if (target_type == RenderSystem::BufferType::TYPE_INDEX) {
        target = GL_ELEMENT_ARRAY_BUFFER;
    }

    glBindBuffer(target, buffer_id);
}


void RenderSystem::createBuffer(uint32_t* buffer) {
    glGenBuffers(1, buffer);
}

void RenderSystem::deleteBuffer(uint32_t* buffer) {
    glDeleteBuffers(1, buffer);
}

void RenderSystem::setupBufferData(
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

    glBufferData(target, size, data, gl_usage);
}

void RenderSystem::setupBufferSubData(
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
}




void RenderSystem::setActiveTextureUnit(
    int unit
) {
    unit += GL_TEXTURE0;
    glActiveTexture(unit);
}







}   // namespace gfx
}   // namespace t3

