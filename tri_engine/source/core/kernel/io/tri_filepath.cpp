

#include "cross/cross_sdk.hpp"
#include "core/kernel/io/tri_filepath.hpp"

TRI_CORE_NS_BEGIN



String FilePath::base_filepath_;

FilePath::FilePath(
    const String& filepath
)   : filepath_(filepath)
    , filename_()
    , ext_()
{
    //  �Ō�̃s���I�h������
    String::size_type last_period(filepath.rfind('.'));
    String::size_type last_slash(filepath.rfind('/'));

    if (last_period != String::npos) {
        //  �Ō�̃s���I�h����悪�g���q
        ext_ = filepath.substr(last_period, filepath.length());
    }

    if (last_slash != String::npos) {
        //  �Ō�̃X���b�V������悪�t�@�C����
        filename_ = filepath.substr(last_slash, filepath.length());
    }


}


FilePath::~FilePath() {
}


void FilePath::setBaseDirectory(
    String base
) {
    base_filepath_ = base;
}


String FilePath::fullpath() const {
    
    return base_filepath_ + filepath_;
}

TRI_CORE_NS_END
