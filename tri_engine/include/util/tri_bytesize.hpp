

#ifndef TRI_BYTE_SIZE_HPP_INCLUDED
#define TRI_BYTE_SIZE_HPP_INCLUDED

//  include
#include <cstdlib>


///
/// バイトサイズ
class ByteSize {

public:
    ///
    /// コンストラクタ
    ByteSize()
        : size_(0)
    {
    }
    
    ///
    /// デストラクタ
    ~ByteSize() = default;

public:
    ///
    /// byteとしてサイズを設定
    void byte(size_t size) {
        size_ = size;
    }
    
    /// byteとしてサイズを取得
    size_t byte() const {
        return size_;
    }

    ///
    /// キロバイトとしてサイズを設定
    void kbyte(size_t size) {
        size_ = size * 1024;
    }
    
    ///
    /// キロバイトとしてサイズを取得
    size_t kbyte() const {
        return size_ / 1024;
    }

    ///
    /// メガバイトとしてサイズを設定
    void mbyte(size_t size) {
        size_ = size * 1024 * 1024;
    }
    
    ///
    /// メガバイトとしてサイズを取得
    size_t mbyte() const {
        return size_ / 1024 / 1024;
    }

    ///
    /// サイズを加算
    void add(size_t size) {
        size_ += size;
    }
    
    ///
    /// サイズを減算
    void sub(size_t size) {
        size_ -= size;
    }


private:
    size_t size_;   ///< サイズ
};




#endif  // TRI_BYTE_SIZE_HPP_INCLUDED
