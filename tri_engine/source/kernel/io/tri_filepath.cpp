//
//  tri_filepath.cpp
//  tri_sandbox_osx
//
//  Created by KANI Tetsuro on 2013/11/11.
//  Copyright (c) 2013年 KANI Tetsuro. All rights reserved.
//

#include <cstring>
#include "tri_filepath.hpp"

namespace t3 {
inline namespace io {


char FilePath::base_filepath_[64];

FilePath::FilePath(
    const char* const filepath
)   : filepath_{""}
{
    std::strncpy(filepath_, base_filepath_, 64);
    std::strncat(filepath_, filepath, 128);
}

FilePath::~FilePath()
{

}


void FilePath::setResourceDirectory(
    const char *const base
) {
    std::strncpy(base_filepath_, base, 64);
}





}   // namespace io
}   // namespace t3
