
#ifndef TRI_RENDER_SYSTEM_HPP
#define TRI_RENDER_SYSTEM_HPP


namespace t3 {
inline namespace gfx {


class RenderSystem {
public:
    enum class CullingMode {
        CULL_MODE_FRONT,
        CULL_MODE_BACK,
    };
    static void setCullingMode(
        CullingMode mode
    );
    
    static void swapBuffers();
    
    static void clearBuffer(
        bool color_clear,
        bool depth_clear,
        bool stencil_clear
    );
    
};


}   // namespace gfx
}   // namespace t3

#endif // TRI_RENDER_SYSTEM_HPP
