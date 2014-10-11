

#include "gfx/tri_render_system.hpp"



#define BEFORE_JUDGE_GL     (0)

#define COUNT_RENDER_CALL   (1)


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

namespace t3 {
inline namespace gfx {

void RenderSystem::setBlendMode(
    t3::RenderSystem::BlendMode mode
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

    clearColor(
        clear_color.redFloat(),
        clear_color.greenFloat(),
        clear_color.blueFloat(),
        clear_color.alphaFloat()
    );
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





}   // namespace gfx
}   // namespace t3

