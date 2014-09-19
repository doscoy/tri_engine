

#include "kernel/io/tri_filepath.hpp"
#include "platform/platform.hpp"


namespace t3 {
inline namespace io {


String FilePath::base_filepath_;

FilePath::FilePath(
    String filepath
)   : filepath_{""}
{
    filepath_ = base_filepath_ + filepath;
}

FilePath::FilePath(
    const char* const filepath
) : filepath_("")
{
    filepath_ = base_filepath_ + filepath;
}


FilePath::~FilePath() {

}


void FilePath::setResourceDirectory(
    String base
) {
    base_filepath_ = base;
}


String FilePath::getExt() const {
    String::size_type pos(filepath_.rfind('.'));
    return (pos != String::npos) ? filepath_.substr(pos, filepath_.length()) : String();
    
}

String FilePath::getFileNameNotExt() const {
    String::size_type pos(filepath_.rfind('.'));
	return filepath_.substr(0, pos);
}


String FilePath::getFullPath() const {
    
    String device_path = platform::getDeviceFilePath();
    String str = device_path + getFileNameNotExt() + getExt();
    return str;
}


}   // namespace io
}   // namespace t3
