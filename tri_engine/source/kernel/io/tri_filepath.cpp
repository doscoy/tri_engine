

#include "kernel/io/tri_filepath.hpp"
#include "platform/platform.hpp"


namespace t3 {
inline namespace io {


String FilePath::base_filepath_;

FilePath::FilePath(
    const String& filepath
)   : filepath_(filepath)
{
}


FilePath::~FilePath() {

}


void FilePath::setBaseDirectory(
    String base
) {
    base_filepath_ = base;
}

const String& FilePath::path() const {
    return filepath_;
}

String FilePath::ext() const {
    String::size_type pos(filepath_.rfind('.'));
    return (pos != String::npos) ? filepath_.substr(pos, filepath_.length()) : String();
    
}

String FilePath::getFileNameNotExt() const {
    String::size_type pos(filepath_.rfind('.'));
	return filepath_.substr(0, pos);
}


String FilePath::getFullPath() const {
    
    String str = base_filepath_ + filepath_;
    return str;
}


}   // namespace io
}   // namespace t3
