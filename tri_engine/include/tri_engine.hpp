////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_engine.hpp
    TriENGINE統合ヘッダー.
*/

#ifndef TRI_ENGINE_HPP_INCLUDED
#define TRI_ENGINE_HPP_INCLUDED

//  include
#include "cross/cross.hpp"
#include "core/core.hpp"
#include "jet/jet.hpp"



//  バージョン情報
//  0.5.0
#define TRI_ENGINE_MAJOR_VERSION    (0 << 16)   // メジャーバージョン
#define TRI_ENGINE_MINOR_VERSION    (5 << 8)    // マイナーバージョン
#define TRI_ENGINE_RELEASE_VERSION  (0)         // リリースバージョン
#define TRI_ENGINE_VERSION  (TRI_ENGINE_MAJOR_VERSION | TRI_ENGINE_MINOR_VERSION | TRI_ENGINE_RELEASE_VERSION)

#endif // TRI_ENGINE_HPP_INCLUDED

