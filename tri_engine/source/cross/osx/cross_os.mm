////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "cross_os.hpp"
#include <cstdio>

CROSS_NS_BEGIN

void printConsole(
    const char* str
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
