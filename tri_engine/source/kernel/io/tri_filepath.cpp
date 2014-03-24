

#include "tri_filepath.hpp"

namespace t3 {
inline namespace io {


std::string FilePath::base_filepath_;

FilePath::FilePath(
    std::string filepath
)   : filepath_{""}
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


}   // namespace io
}   // namespace t3
