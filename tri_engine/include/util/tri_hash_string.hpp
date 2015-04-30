#ifndef TRI_HASH_STRING_HPP_INCLUDED
#define TRI_HASH_STRING_HPP_INCLUDED


#include "base/tri_std.hpp"


namespace t3 {
    
    
class HashString {

public:
    using key_t = std::size_t;

public:
    HashString()
        : str_()
        , key_()
    {
    }

    explicit HashString(const String str)
        : str_(str)
        , key_(strToHashKey(str))
    {
    }
    
    ~HashString() = default;
    
    
    
public:
    String string() const {
        return str_;
    }
    
    key_t key() const {
        return key_;
    }
    
    void setString(const String str) {
        str_ = str;
        key_ = strToHashKey(str);
    }

public:
    bool operator <(const HashString& rhs) const {
        return key_ < rhs.key_;
    }
    
    
    bool operator ==(const HashString& rhs) const {
        return key_ == rhs.key_;
    }
    
private:
    
    key_t strToHashKey(
        const String str
    ) {
        return std::hash<String>()(str);
    }
    
private:
    String str_;
    key_t key_;

};
    
    
}   // namespace t3

#endif  // TRI_HASH_STRING
