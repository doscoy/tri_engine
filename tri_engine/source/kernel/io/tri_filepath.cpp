

#include "kernel/io/tri_filepath.hpp"
#include "platform/platform.hpp"


namespace t3 {
inline namespace io {


std::string FilePath::base_filepath_;

FilePath::FilePath(
    std::string filepath
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
    std::string base
) {
    base_filepath_ = base;
}


std::string FilePath::getExt() const {
    std::string::size_type pos(filepath_.rfind('.'));
    return (pos != std::string::npos) ? filepath_.substr(pos, filepath_.length()) : std::string();
    
}

std::string FilePath::getFileNameNotExt() const {
    std::string::size_type pos(filepath_.rfind('.'));
	return filepath_.substr(0, pos);
}


std::string FilePath::getFullPath() const {
    
    std::string device_path = platform::getDeviceFilePath();
    std::string str = device_path + getFileNameNotExt() + getExt();
    return str;
}


}   // namespace io
}   // namespace t3
