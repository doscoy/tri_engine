#include "util/tri_text_loader.hpp"
#include "kernel/io/tri_file.hpp"

namespace t3 {

String loadText(
    const char* const path
) {
    File file;
    file.loadFile(path, File::IOMode::IN, File::IOType::TEXT);
    return String(reinterpret_cast<const char*>(file.data()));
}

}   // namespace t3
