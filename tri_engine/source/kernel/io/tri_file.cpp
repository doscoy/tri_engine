
#include "tri_file.hpp"
#include "base/tri_types.hpp"
#include "kernel/memory/tri_memory.hpp"
#include "dbg/tri_assert.hpp"
#include "platform/platform.hpp"
#include <fstream>

//==============================================================================
namespace t3 {

    
// *********************************************
//  コンストラクタ
File::File()    
    : data_(nullptr)
    , size_(0)
{

}    
    
// *********************************************
//  デストラクタ
File::~File()
{
    T3_FREE(data_);
}
    
    
    
// *********************************************
//  ファイル読み込み
bool File::loadFile(
    const FilePath& filepath
){
    std::string path = filepath.getFullPath();
    std::ifstream fs(path);                 //ファイルオープン。読み込み形式は指定なしのときはテキストモードになる。
    
    T3_ASSERT(!fs.fail());
    fs.seekg( 0, std::fstream::end );       //ファイル末尾を探す
    filesize_t eof_pos = fs.tellg();        //ファイル末尾インデクスを取得
    fs.clear();
    fs.seekg( 0, std::fstream::beg );       //ファイル先頭に戻る
    filesize_t beg_pos = fs.tellg();        //ファイル先頭インデクスを取得
    size_ = eof_pos - beg_pos;              //末尾-先頭でファイルサイズを計算
    
    data_ = (uint8_t*)T3_ALLOC(size_);
    
    fs.read((char*)data_, size_);                //ファイル先頭からバッファへコピー
    


//    platform::loadFile(filepath, &data_, &size_);
    return true;
}
    

    
    
}   // namespace t3










