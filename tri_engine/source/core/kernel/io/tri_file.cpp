
#include "core/kernel/io/tri_file.hpp"
#include "core/base/tri_types.hpp"
#include "core/kernel/memory/tri_memory.hpp"
#include "core/debug/tri_assert.hpp"

#include <fstream>

//==============================================================================
TRI_CORE_NS_BEGIN


    
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
    const FilePath& filepath,
    File::IOMode mode,
    File::IOType type
) {
    return loadFile(filepath.fullpath().c_str(), mode, type);
}
    
    
//  ファイル読み込み
bool File::loadFile(
    const char* const path,
    File::IOMode mode,
    File::IOType type
) {
    int flag = 0;
    if (mode == IOMode::IN) {
        flag |= std::ios::in;
    } else {
        flag |= std::ios::out;
    }
    
    if (type == IOType::BINARY) {
        flag |= std::ios::binary;
    }
    
    name_ = path;
    FileStream fs;
    //  ファイルオープン。読み込み形式は指定なしのときはテキストモードになる。
    fs.open(path, flag);
    
    T3_ASSERT_MSG(!fs.fail(), "filepath = %s", path);
    //  ファイル末尾を探す
    fs.seekg( 0, std::fstream::end );
    
    //  ファイル末尾インデクスを取得
    std::size_t eof_pos = static_cast<std::size_t>(fs.tellg());
    fs.clear();
    //  ファイル先頭に戻る
    fs.seekg( 0, std::fstream::beg );
    
    //  ファイル先頭インデクスを取得
    std::size_t beg_pos = static_cast<std::size_t>(fs.tellg());
    fs.clear();
    
    //  サイズ取得
    //  末尾-先頭でファイルサイズを計算
    size_ = eof_pos - beg_pos + 1;
    if (auto_free_) {
        T3_FREE(data_);
    }
    data_ = (uint8_t*)T3_SYS_ALLOC(size_);
    std::memset(data_, 0, size_);
    auto_free_ = true;

    //  データ保持
    //  ファイル先頭からバッファへコピー
    fs.read((char*)data_, size_);
    T3_ASSERT(!fs.bad());

    
    return true;
}
    

    
TRI_CORE_NS_END



