
#ifndef TRI_FILE_HPP_INCLUDED
#define TRI_FILE_HPP_INCLUDED

#include "util/tri_uncopyable.hpp"
#include "base/tri_types.hpp"
#include "base/tri_std.hpp"
#include "tri_filepath.hpp"

namespace t3 {


class File : private Uncopyable
{
public:
    File();
    File(uint8_t* data, size_t size);
    ~File();

public:

    //  ファイル読み込み
    bool loadFile(const FilePath& filepath);

    //  データ取得
    const uint8_t* getData() const {
        return data_;
    }
    
    //  データサイズ取得
    std::size_t size() const {
        return size_;
    }
    
    //  正当性チェック
    bool isVaild() const {
        return  data_ != nullptr;
    }

    
private:
    //  データ
    uint8_t* data_;
    
    //  データサイズ
    std::size_t size_;
    
};
    
using FilePtr = SharedPtr<File>;
    
}   // namespace t3



#endif // TRI_FILE_HPP_INCLUDED