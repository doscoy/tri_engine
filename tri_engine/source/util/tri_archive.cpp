//  include
#include "util/tri_archive.hpp"
#include "kernel/memory/tri_new.hpp"

namespace t3 {


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


}   // namespace t3



