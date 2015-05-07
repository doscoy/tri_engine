

#ifndef TRI_BYTE_SIZE_HPP_INCLUDED
#define TRI_BYTE_SIZE_HPP_INCLUDED

//  include
#include <cstdlib>


///
/// �o�C�g�T�C�Y
class ByteSize {

public:
    ///
    /// �R���X�g���N�^
    ByteSize()
        : size_(0)
    {
    }
    
    ///
    /// �f�X�g���N�^
    ~ByteSize() = default;

public:
    ///
    /// byte�Ƃ��ăT�C�Y��ݒ�
    void byte(size_t size) {
        size_ = size;
    }
    
    /// byte�Ƃ��ăT�C�Y���擾
    size_t byte() const {
        return size_;
    }

    ///
    /// �L���o�C�g�Ƃ��ăT�C�Y��ݒ�
    void kbyte(size_t size) {
        size_ = size * 1024;
    }
    
    ///
    /// �L���o�C�g�Ƃ��ăT�C�Y���擾
    size_t kbyte() const {
        return size_ / 1024;
    }

    ///
    /// ���K�o�C�g�Ƃ��ăT�C�Y��ݒ�
    void mbyte(size_t size) {
        size_ = size * 1024 * 1024;
    }
    
    ///
    /// ���K�o�C�g�Ƃ��ăT�C�Y���擾
    size_t mbyte() const {
        return size_ / 1024 / 1024;
    }

    ///
    /// �T�C�Y�����Z
    void add(size_t size) {
        size_ += size;
    }
    
    ///
    /// �T�C�Y�����Z
    void sub(size_t size) {
        size_ -= size;
    }


private:
    size_t size_;   ///< �T�C�Y
};




#endif  // TRI_BYTE_SIZE_HPP_INCLUDED
