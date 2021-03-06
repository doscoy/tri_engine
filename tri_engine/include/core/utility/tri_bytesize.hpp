////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_bytesize.hpp
    バイトサイズの単位変換.
*/

#ifndef TRI_BYTE_SIZE_HPP_INCLUDED
#define TRI_BYTE_SIZE_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include <cstdlib>

TRI_CORE_NS_BEGIN


///
/// バイトサイズ
class ByteSize {

public:
    ///
    /// コンストラクタ
    ByteSize()
        : size_(0)
    {
    }
    
    ///
    /// デストラクタ
    ~ByteSize() = default;

public:
    ///
    /// byteとしてサイズを設定
    void byte(size_t size) {
        size_ = size;
    }
    
    /// byteとしてサイズを取得
    size_t byte() const {
        return size_;
    }

    ///
    /// キロバイトとしてサイズを設定
    void kbyte(size_t size) {
        size_ = size * 1024;
    }
    
    ///
    /// キロバイトとしてサイズを取得
    size_t kbyte() const {
        return size_ / 1024;
    }

    ///
    /// メガバイトとしてサイズを設定
    void mbyte(size_t size) {
        size_ = size * 1024 * 1024;
    }
    
    ///
    /// メガバイトとしてサイズを取得
    size_t mbyte() const {
        return size_ / 1024 / 1024;
    }

    ///
    /// サイズを加算
    void add(size_t size) {
        size_ += size;
    }
    
    ///
    /// サイズを減算
    void sub(size_t size) {
        size_ -= size;
    }


private:
    size_t size_;   ///< サイズ
};


TRI_CORE_NS_END

#endif  // TRI_BYTE_SIZE_HPP_INCLUDED
