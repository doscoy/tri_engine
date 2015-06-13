
#include "cross_render_system.hpp"
#include "cross_os.hpp"
#include "cstdio"
#include <sys/time.h>
namespace cross {
void printConsole(
    const char* const str
) {
    std::printf(str);
}

std::string getDeviceFilePath() {
#if DEBUG

    return std::string("/Users/kani/project/tri_engine/samples/resources/");

#else
    return std::string("");
#endif
}





}   // namespace cross
