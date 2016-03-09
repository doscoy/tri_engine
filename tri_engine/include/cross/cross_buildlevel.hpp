////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file cross_buildlevel.hpp
    TRI_ENGINEのビルドレベル制御.
*/
#ifndef CROSS_BUILD_LEVEL_HPP_INCLUDED
#define CROSS_BUILD_LEVEL_HPP_INCLUDED

//  各種開発環境でのデバッグシンボルがまちまちなので吸収する
//  どれか定義されてればデバッグビルド
#if defined( _DEBUG ) || defined( DEBUG ) || defined (__DEBUG__)
#   ifndef TRI_DEBUG
#       define TRI_DEBUG
#   endif
#endif



#endif // CROSS_BUILD_LEVEL_HPP_INCLUDED
