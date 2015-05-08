#ifndef TRI_HASH_STRING_HPP_INCLUDED
#define TRI_HASH_STRING_HPP_INCLUDED

//  include
#include "base/tri_std.hpp"


namespace t3 {
    
///
/// �n�b�V���l�t������
class HashString {

public:
    //  �n�b�V���L�[
    using key_t = std::size_t;

public:
    ///
    /// �R���X�g���N�^
    HashString()
        : str_()
        , key_()
    {}

    ///
    /// �R���X�g���N�^
    explicit HashString(const String str)
        : str_(str)
        , key_(strToHashKey(str))
    {
    }
    
    ///
    /// �f�X�g���N�^
    ~HashString() = default;
    
    
    
public:
    ///
    /// ������擾
    String string() const {
        return str_;
    }
    
    ///
    /// �n�b�V���l�擾
    key_t key() const {
        return key_;
    }
    
    ///
    /// �������ݒ�
    void setString(const String str) {
        str_ = str;
        key_ = strToHashKey(str);
    }

public:
    ///
    /// ������̔�r
    bool operator <(const HashString& rhs) const {
        return key_ < rhs.key_;
    }
    
    
    ///
    /// ������̔�r
    bool operator ==(const HashString& rhs) const {
        return key_ == rhs.key_;
    }
    
private:
    
    ///
    /// ��������n�b�V���l�ɕϊ�
    key_t strToHashKey(
        const String str
    ) {
        return std::hash<String>()(str);
    }
    
private:
    String str_;    ///< ������
    key_t key_;     ///< �n�b�V���l

};
    
    
}   // namespace t3

#endif  // TRI_HASH_STRING
