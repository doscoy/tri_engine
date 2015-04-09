#ifndef CROSS_BASE_HPP_INCLUDED
#define CROSS_BASE_HPP_INCLUDED



#include "cross_types.hpp"


namespace cross {



void initializePlatform();


void terminatePlatform();
void beginUpdate();
void endUpdate();
void platformPadData(
    int no,
    GamePadData* data
);

void platformPointingData(
    int no,
    PointingData* data
);


bool isExitRequest();

void printConsole(
    const char* const str
);

String getDeviceFilePath();

void loadFile(
    const char* const file_path,
    uint8_t** data,
    size_t* size
);

void saveInteger(
    const char* const label,
    int val
);

void loadInteger(
    const char* const label,
    int* key
);







}   // namespace cross

#endif // PLATFORM_HPP_INCLUDED
