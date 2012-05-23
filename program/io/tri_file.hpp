
#ifndef TRI_FILE_HPP_INCLUDED
#define TRI_FILE_HPP_INCLUDED

#include "../util/tri_uncopyable.hpp"
#include "base/tri_types.hpp"

namespace t3 {


class File : private Uncopyable
{
public:
    File();
    ~File();

public:

    // *********************************************
    //  ファイル読み込み
    bool loadFile( const char* const path );

    // *********************************************
    //  データ取得
    const byte* getData() const {
        return data_;
    }
    
    // *********************************************
    //  データサイズ取得
    std::size_t getDataSize() const {
        return size_;
    }
    
    // *********************************************
    //  正当性チェック
    bool isVaild() const {
        return  data_ != nullptr;
    }

    
    // *********************************************
    //  内容をダンプ
    void dump() const;
    
private:
    //  データ
    byte* data_;
    
    //  データサイズ
    std::size_t size_;
    
};
    
    
}   // namespace t3



#endif // TRI_FILE_HPP_INCLUDED