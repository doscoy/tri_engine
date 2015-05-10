#ifndef TRI_UNIQUE_ID_HPP_INCLUDED
#define TRI_UNIQUE_ID_HPP_INCLUDED

//  include
#include "base/tri_std.hpp"
#include "tri_uncopyable.hpp"


namespace t3 {


///
/// ユニークID生成クラス
class UniqueID {
public:
    ///
    /// コンストラクタ
    UniqueID();

public:
    ///
    /// operator ==
    bool operator ==(const UniqueID& rhs) const {
        return uid_ == rhs.uid_;
    }
    
    ///
    /// operator !=
    bool operator !=(const UniqueID& rhs) const {
        return uid_ != rhs.uid_;
    }
    
    ///
    /// operator >
    bool operator >(const UniqueID& rhs) const {
        return uid_ > rhs.uid_;
    }

    ///
    /// operator <
    bool operator <(const UniqueID& rhs) const {
        return uid_ < rhs.uid_;
    }

    ///
    /// operator <=
    bool operator <=(const UniqueID& rhs) const {
        return uid_ <= rhs.uid_;
    }
    
    ///
    /// operator >=
    bool operator >=(const UniqueID& rhs) const {
        return uid_ >= rhs.uid_;
    }
    
private:
    ///
    /// ユニークID
    uint32_t uid_;
    
    ///
    /// ユニークID生成用
    static uint32_t uid_generator_;
};



}   // namespace t3

#endif // TRI_UNIQUE_ID_HPP_INCLUDED
