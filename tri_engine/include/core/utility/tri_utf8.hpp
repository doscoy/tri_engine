////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_utf8.hpp
    UTF-8.
*/
#ifndef tri_engine_tri_utf8string_hpp
#define tri_engine_tri_utf8string_hpp

//  include
#include "core/core_config.hpp"
#include "cross/cross_std.hpp"


TRI_CORE_NS_BEGIN


///
/// utf8のバイトサイズ取得
int utf8ByteSize(const char* const a);

///
/// utf8文字としての比較
bool isCompUTF8Char(const char* const a, const char* const b);

///
/// UTF8文字列
class Utf8 {
public:
    ///
    /// コンストラクタ
    Utf8(const char* const str);

    ///
    /// デストラクタ
    ~Utf8();


public:
    ///
    /// 文字列の長さ取得
    int length() const {
        return  size_;
    }
    
    ///
    /// 文字取得
    const char* at(int idx) const {
        return char_pos_.at(idx);
    }

private:
    ///
    /// 文字サイズ
    uint32_t size_;

    ///
    /// 文字
    Vector<char*> char_pos_;

    ///
    /// 生データ
    String raw_;
};


TRI_CORE_NS_END



#endif
