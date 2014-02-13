#include "gfx/tri_render_system.hpp"
#include "platform/platform_sdk.hpp"

extern GLFWwindow* window_;


namespace t3 {
inline namespace gfx {
    
    
void RenderSystem::swapBuffers() {
    glfwSwapBuffers(window_);
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
        case CullingMode::CULL_MODE_BACK:
            cull_flag = GL_BACK;
            break;
        
        case CullingMode::CULL_MODE_FRONT:
            cull_flag = GL_FRONT;
            break;
            
        default:
            break;
    }
    
    glCullFace(cull_flag);
}

}   // namespace gfx
}   // namespace t3