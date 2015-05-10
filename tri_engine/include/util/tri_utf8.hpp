
#ifndef tri_engine_tri_utf8string_hpp
#define tri_engine_tri_utf8string_hpp

//  include
#include "base/tri_std.hpp"

namespace t3 {

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


}   // namespace t3



#endif
