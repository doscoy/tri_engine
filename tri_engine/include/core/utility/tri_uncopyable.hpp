////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_uncopyable.hpp
    コピー禁止ミックスインクラス.
*/
#ifndef TRI_UNCOPYABLE_HPP_INCLUDED
#define TRI_UNCOPYABLE_HPP_INCLUDED


#include "core/core_config.hpp"


TRI_CORE_NS_BEGIN


///
///  コピー禁止ミックスイン
class Uncopyable {
protected:
    Uncopyable() = default;
    ~Uncopyable() = default;
    Uncopyable( const Uncopyable& ) = delete;
    Uncopyable& operator= ( const Uncopyable& ) = delete;
};


TRI_CORE_NS_END


#endif // TRI_UNCOPYABLE_HPP_INCLUDED
