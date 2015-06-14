/**
    @file tri_nameable.hpp
    名前を持つクラス.
*/

#ifndef TRI_NAMEABLE_HPP_INCLUDED
#define TRI_NAMEABLE_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "tri_hash_string.hpp"

TRI_CORE_NS_BEGIN



///
/// 名前を持つクラス
class Nameable {
public:
    ///
    /// コンストラクタ
    Nameable()
        : name_()
    {}
    
    ///
    /// コンストラクタ
    Nameable(const String& name)
        : name_(name)
    {}
    
    ///
    /// デストラクタ
    virtual ~Nameable()
    {}
    
public:
    ///
    /// 名前取得
    String name() const {
        return name_.string();
    }
    
    ///
    /// 名前のハッシュ値取得
    t3::HashString::key_t getNameHash() {
        return name_.key();
    }

    ///
    /// 名前設定
    void name(const String name) {
        name_.setString(name);
    }

private:
    ///
    /// 名前
    t3::HashString name_;
};

TRI_CORE_NS_END


#endif  //  TRI_NAMEABLE_HPP_INCLUDED

