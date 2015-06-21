//
//  cross_glfw.hpp
//  tri_engine
//
//  Created by KANI Tetsuro on 2015/06/03.
//  Copyright (c) 2015年 KANI Tetsuro. All rights reserved.
//

#ifndef tri_engine_cross_glfw_hpp
#define tri_engine_cross_glfw_hpp


#if CROSS_TARGET_PLATFORM == CROSS_TARGET_PLATFORM_WIN32
#include <glew.h>
#include <glfw3.h>
#else 
#define GLFW_EXPOSE_NATIVE_COCOA
//
// glのヘッダーへのパスを各自の環境にあわせて通して下さい
// ex. macportsで入れてる場合は opt/local/include等
#include "GL/glew.h"
#include "GL/gl.h"
#include "GL/glext.h"
#include "GLFW/glfw3.h"
//#include "GLFW/glfw3native.h"
#endif

#endif
