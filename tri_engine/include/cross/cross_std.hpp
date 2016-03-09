////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file cross_std.hpp
    c++標準ヘッダ群インクルード用.
*/

#ifndef CROSS_STD_HPP_INCLUDED
#define CROSS_STD_HPP_INCLUDED

//  include
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdarg>
#include <cstddef>
#include <cassert>
#include <cmath>
#include <string>
#include <set>
#include <memory>
#include <memory.h>
#include <map>
#include <vector>
#include <limits.h>
#include <list>
#include <functional>
#include <fstream>
#include <functional>
#include <thread>
#include <regex>


#include "cross_config.hpp"

CROSS_NS_BEGIN

//  関数
inline bool isNan(float f) {
    return std::isnan(f);
}

inline bool isInf(float f) {
    return std::isinf(f);
}


//  型定義

///
/// スマートポインタ
template <typename T>
using SharedPtr = std::shared_ptr<T>;

template <typename T>
using WeakPtr = std::weak_ptr<T>;

///
/// スマートポインタ.
/// コピー禁止
template <typename T>
using UniquePtr = std::unique_ptr<T>;

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

///
/// 数値限界
template <typename T>
using NumericLimits = std::numeric_limits<T>;


CROSS_NS_END


#endif  // CROSS_STD_HPP_INCLUDED
