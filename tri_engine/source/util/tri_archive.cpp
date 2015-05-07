//  include
#include "util/tri_archive.hpp"
#include "kernel/memory/tri_new.hpp"

namespace t3 {


//  �A�[�J�C�u�̓ǂݍ���
void Archive::load(const String& arcname) {
    zip_.initialize(arcname);
}

//  �A�[�J�C�u�̓W�J
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

//  �t�@�C���擾
const File* Archive::file(
    const String& filename
) {
    //  �w��t�@�C�����̃t�@�C�������邩����
    for (auto& f : files_) {
        if (f->name() == filename) {
            return f;
        }
    }
    
    //  ��������
    return nullptr;
}


}   // namespace t3



