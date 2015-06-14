

#include "cross_os.hpp"
#include "cstdio"

CROSS_NS_BEGIN

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




CROSS_NS_END
