
#ifndef TRI_RENDERABLE_HPP_INCLUDED
#define TRI_RENDERABLE_HPP_INCLUDED

namespace t3 {
inline namespace gfx {

class IRenderer;

class IRenderable
{
public:
    virtual void render(IRenderer*) = 0;
};


}   // namespace gfx
}   // namespace t3


#endif // TRI_RENDERABLE_HPP_INCLUDED