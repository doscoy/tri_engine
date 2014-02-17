
#include <fstream>
#include <iostream>
#include "tri_file.hpp"
#include "base/tri_types.hpp"
#include "kernel/memory/tri_memory.hpp"
#include "dbg/tri_assert.hpp"

//==============================================================================
namespace t3 {

    
// *********************************************
//  コンストラクタ
File::File()    
    : data_( nullptr )
    , size_( 0 )
{

}    
    
// *********************************************
//  デストラクタ
File::~File()
{
    T3_FREE( data_ );
}
    
    
    
// *********************************************
//  ファイル読み込み
bool File::loadFile(
    const char* const path
){

    std::ifstream fs(path);                 //ファイルオープン。読み込み形式は指定なしのときはテキストモードになる。

    T3_ASSERT(!fs.fail());
    fs.seekg( 0, std::fstream::end );       //ファイル末尾を探す
    filesize_t eof_pos = fs.tellg();        //ファイル末尾インデクスを取得
    fs.clear();
    fs.seekg( 0, std::fstream::beg );       //ファイル先頭に戻る
    filesize_t beg_pos = fs.tellg();        //ファイル先頭インデクスを取得
    size_ = eof_pos - beg_pos;              //末尾-先頭でファイルサイズを計算
    
    data_ = T3_ALLOC( size_ );
    
    fs.read( data_, size_ );                //ファイル先頭からバッファへコピー

    return true;
}
    
// *********************************************
//  ファイル情報をダンプ
void File::dump() const {
    std::cout << data_ << "(" << size_ << ")" << std::endl;
}

    
    
}   // namespace t3










