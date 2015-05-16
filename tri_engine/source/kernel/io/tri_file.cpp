
#include "kernel/io/tri_file.hpp"
#include "base/tri_types.hpp"
#include "kernel/memory/tri_memory.hpp"
#include "dbg/tri_assert.hpp"

#include <fstream>

//==============================================================================
namespace t3 {

    
//  コンストラクタ
File::File()    
    : File(String(""), 0, nullptr)
{

}    

//  コンストラクタ
File::File(
    const String& name,
    size_t size
)   : name_(name)
    , data_((uint8_t*)T3_SYS_ALLOC(size))
    , size_(size)
    , auto_free_(true)
{
}


//  コンストラクタ
File::File(
    const String& name,
    size_t size,
    uint8_t* data
)   : name_(name)
    , data_(data)
    , size_(size)
    , auto_free_(false)
{
}

    
//  デストラクタ
File::~File()
{
    if (auto_free_) {
        T3_FREE(data_);
    }
}
    
    
    
//  ファイル読み込み
bool File::loadFile(
    const FilePath& filepath
) {
    
    String path = filepath.fullpath();
    name_ = filepath.path();
    FileStream fs;
    fs.open(path, std::ios_base::binary | std::ios::in);                 //ファイルオープン。読み込み形式は指定なしのときはテキストモードになる。
    
    T3_ASSERT_MSG(!fs.fail(), "filepath = %s", path.c_str());
    fs.seekg( 0, std::fstream::end );       //ファイル末尾を探す
    std::size_t eof_pos = static_cast<std::size_t>(fs.tellg());        //ファイル末尾インデクスを取得
    fs.clear();
    fs.seekg( 0, std::fstream::beg );       //ファイル先頭に戻る
    std::size_t beg_pos = static_cast<std::size_t>(fs.tellg());        //ファイル先頭インデクスを取得
    fs.clear();
    
    //  サイズ取得
    size_ = eof_pos - beg_pos + 1;              //末尾-先頭でファイルサイズを計算
    if (auto_free_) {
        T3_FREE(data_);
    }
    data_ = (uint8_t*)T3_SYS_ALLOC(size_);
    std::memset(data_, 0, size_);
    auto_free_ = true;

    //  データ保持
    fs.read((char*)data_, size_);                //ファイル先頭からバッファへコピー
    T3_ASSERT(!fs.bad());

    std::size_t fin = static_cast<std::size_t>(fs.tellg());        //ファイル先頭インデクスを取得
    
    return true;
}
    

    
}   // namespace t3



