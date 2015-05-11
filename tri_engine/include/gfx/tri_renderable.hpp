/**
    @file tri_renderable.hpp
    描画可能オブジェクト.
*/

#ifndef TRI_RENDERABLE_HPP_INCLUDED
#define TRI_RENDERABLE_HPP_INCLUDED

namespace t3 {

//  include
class IRenderer;


///
/// レンダリングオブジェクトインターフェース
class IRenderable
{
public:
    ///
    /// 描画
    virtual void render(
        IRenderer* r    ///< レンダラ
    ) = 0;
};


}   // namespace t3


#endif // TRI_RENDERABLE_HPP_INCLUDED