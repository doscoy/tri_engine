#ifndef PLATFORM_SDK_HPP_INCLUDED
#define PLATFORM_SDK_HPP_INCLUDED

#include <cstdint>

#if defined(_WIN32)

#elif defined(__APPLE__)
#include "../../third_party_lib/osx/png.h"
#include "../../third_party_lib/osx/GLFW/glfw3.h"
#endif


#endif // PLATFORM_SDK_HPP_INCLUDED