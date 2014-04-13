#ifndef TRI_HASH_STRING_HPP_INCLUDED
#define TRI_HASH_STRING_HPP_INCLUDED

#include <functional>
#include <string>


namespace t3 {
inline namespace util {
    
    
class HashString {

public:
    using key_t = std::size_t;

public:
    explicit HashString(const std::string str)
        : str_(str)
        , key_(strToHashKey(str))
    {}
    
    ~HashString() = default;
    
    
    
public:
    std::string string() const {
        return str_;
    }
    
    key_t key() const {
        return key_;
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
        const std::string str
    ) {
        return std::hash<std::string>()(str);
    }
    
private:
    std::string str_;
    key_t key_;

};
    
    
}   // namespace util
}   // namespace t3

#endif  // TRI_HASH_STRING
