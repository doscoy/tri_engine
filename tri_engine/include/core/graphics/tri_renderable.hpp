////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_renderable.hpp
    描画可能オブジェクト.
*/

#ifndef TRI_RENDERABLE_HPP_INCLUDED
#define TRI_RENDERABLE_HPP_INCLUDED

#include "core/core_config.hpp"


TRI_CORE_NS_BEGIN


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


TRI_CORE_NS_END


#endif // TRI_RENDERABLE_HPP_INCLUDED