#include "utility/tri_text_loader.hpp"
#include "kernel/io/tri_file.hpp"

TRI_CORE_NS_BEGIN


String loadText(
    const char* const path
) {
    File file;
    file.loadFile(path, File::IOMode::IN, File::IOType::TEXT);
    return String(reinterpret_cast<const char*>(file.data()));
}

TRI_CORE_NS_END
