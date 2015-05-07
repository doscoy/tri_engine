
#include "cross_os.hpp"
#include "cstdio"

namespace cross {

void initializePlatform() {


}


void terminatePlatform() {


}

void beginUpdate() {

}

void endUpdate() {

}

void platformPadData(
    int no,
    GamePadData* data
) {

}

void platformPointingData(
    int no,
    PointingData* data
) {


}

bool isExitRequest() {

    return false;
}

void printConsole(
    const char* const str
) {
    std::printf(str);
}

String getDeviceFilePath() {

    return String();
}

}   // namespace cross
