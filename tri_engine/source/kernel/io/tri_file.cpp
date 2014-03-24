
#include "tri_file.hpp"
#include "base/tri_types.hpp"
#include "kernel/memory/tri_memory.hpp"
#include "dbg/tri_assert.hpp"
#include "platform/platform.hpp"


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

    platform::loadFile(filepath, &data_, &size_);
    return true;
}
    

    
    
}   // namespace t3










