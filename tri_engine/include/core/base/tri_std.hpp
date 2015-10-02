////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_std.hpp
    c++標準ヘッダ群インクルード用.
*/

#ifndef tri_engine_tri_std_hpp
#define tri_engine_tri_std_hpp

//  include
#include "core/core_config.hpp"
#include <cstdint>
#include <string>
#include <memory>
#include <memory.h>
#include <vector>
#include <list>
#include <array>
#include <map>
#include <set>
#include <cstdio>
#include <cstdarg>
#include <fstream>
#include <functional>
#include <thread>
#include <cstddef>


TRI_CORE_NS_BEGIN



///
/// スマートポインタ
template <typename T>
using SharedPtr = std::shared_ptr<T>;
  
///
/// スマートポインタ.
/// コピー禁止
template <typename T>
using ScopedPtr = std::unique_ptr<T>;

///
/// ベクターコンテナ
template <typename T>
using Vector = std::vector<T>;

///
/// リストコンテナ
template <typename T>
using List = std::list<T>;

///
/// マップコンテナ
template <typename Key, typename T, typename Comp>
using Map = std::map<Key, T, Comp>;

///
/// 固定長配列コンテナ
template <typename T, size_t Size>
using Array = std::array<T, Size>;

///
/// セットコンテナ
template <typename Key>
using Set = std::set<Key>;

///
/// 文字列クラス
using String = std::string;
  
///
/// スレッド
using Thread = std::thread;

///
/// ファイルストリーム
using FileStream = std::ifstream;
  
TRI_CORE_NS_END


#endif
