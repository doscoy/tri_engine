//
//  cross_glfw.hpp
//  tri_engine
//
//  Created by KANI Tetsuro on 2015/06/03.
//  Copyright (c) 2015年 KANI Tetsuro. All rights reserved.
//

#ifndef tri_engine_cross_glfw_hpp
#define tri_engine_cross_glfw_hpp

#if 0
#include <glew.h>
#include <glfw3.h>
#else 
#define GLFW_EXPOSE_NATIVE_COCOA
#include "GL/glew.h"
#include "GL/gl.h"
#include "GL/glext.h"
#include "GLFW/glfw3.h"
//#include "GLFW/glfw3native.h"
#endif

#endif
