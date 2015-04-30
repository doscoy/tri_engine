//
//  tri_archive.hpp
//  tri_engine
//
//  Created by KANI Tetsuro on 2014/09/23.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#ifndef tri_engine_tri_archive_hpp
#define tri_engine_tri_archive_hpp


#include "tri_zipfile.hpp"
#include "base/tri_std.hpp"
#include "kernel/io/tri_file.hpp"


namespace t3 {


class Archive {

public:
    Archive();
    ~Archive();


public:
    void load(const String& arcname);
    void decompressAll();
    const File* getFile(const String& filename);


private:
    ZipFile zip_;
    Vector<File*> files_;
};



}   // namespace t3





#endif
