////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
//  include
#include "core/utility/tri_archive.hpp"
#include "core/kernel/memory/tri_new.hpp"

TRI_CORE_NS_BEGIN



//  アーカイブの読み込み
void Archive::load(const String& arcname) {
    zip_.initialize(arcname);
}

//  アーカイブの展開
void Archive::decompressAll() {
    int entry_num = zip_.entries();
    for (int i = 0; i < entry_num; ++i) {
        String filename = zip_.getFileName(i);
        size_t buffer_size = zip_.getFileSize(i);
        if (buffer_size == 0) {
            buffer_size = 1;
        }
        File* file = T3_SYS_NEW File(filename, buffer_size);
        zip_.readFile(i, file->data());
        files_.push_back(file);
    }
}

//  ファイル取得
const File* Archive::file(
    const String& filename
) {
    //  指定ファイル名のファイルがあるか調査
    for (auto& f : files_) {
        if (f->name() == filename) {
            return f;
        }
    }
    
    //  無かった
    return nullptr;
}


TRI_CORE_NS_END



