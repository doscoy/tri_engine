#ifndef TRI_HASH_STRING_HPP_INCLUDED
#define TRI_HASH_STRING_HPP_INCLUDED

//  include
#include "base/tri_std.hpp"


namespace t3 {
    
///
/// ハッシュ値付文字列
class HashString {

public:
    //  ハッシュキー
    using key_t = std::size_t;

public:
    ///
    /// コンストラクタ
    HashString()
        : str_()
        , key_()
    {}

    ///
    /// コンストラクタ
    explicit HashString(const String str)
        : str_(str)
        , key_(strToHashKey(str))
    {
    }
    
    ///
    /// デストラクタ
    ~HashString() = default;
    
    
    
public:
    ///
    /// 文字列取得
    String string() const {
        return str_;
    }
    
    ///
    /// ハッシュ値取得
    key_t key() const {
        return key_;
    }
    
    ///
    /// 文字列を設定
    void setString(const String str) {
        str_ = str;
        key_ = strToHashKey(str);
    }

public:
    ///
    /// 文字列の比較
    bool operator <(const HashString& rhs) const {
        return key_ < rhs.key_;
    }
    
    
    ///
    /// 文字列の比較
    bool operator ==(const HashString& rhs) const {
        return key_ == rhs.key_;
    }
    
private:
    
    ///
    /// 文字列をハッシュ値に変換
    key_t strToHashKey(
        const String str
    ) {
        return std::hash<String>()(str);
    }
    
private:
    String str_;    ///< 文字列
    key_t key_;     ///< ハッシュ値

};
    
    
}   // namespace t3

#endif  // TRI_HASH_STRING
