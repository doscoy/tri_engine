

#ifndef TRI_BYTE_SIZE_HPP_INCLUDED
#define TRI_BYTE_SIZE_HPP_INCLUDED

#include <cstdlib>


class ByteSize {

public:
    ByteSize()
        : size_(0)
    {
    }
    
    ~ByteSize() = default;

public:

    void byte(size_t size) {
        size_ = size;
    }
    
    size_t byte() const {
        return size_;
    }

    void kbyte(size_t size) {
        size_ = size * 1024;
    }
    
    size_t kbyte() const {
        return size_ / 1024;
    }

    void mbyte(size_t size) {
        size_ = size * 1024 * 1024;
    }
    
    size_t mbyte() const {
        return size_ / 1024 / 1024;
    }


    void add(size_t size) {
        size_ += size;
    }
    
    void sub(size_t size) {
        size_ -= size;
    }


private:
    size_t size_;
};




#endif  // TRI_BYTE_SIZE_HPP_INCLUDED
