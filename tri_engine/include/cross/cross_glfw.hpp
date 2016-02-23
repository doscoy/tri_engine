////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#ifndef TRI_CROSS_GLFW_HPP_INCLUDED
#define TRI_CROSS_GLFW_HPP_INCLUDED


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

#endif // TRI_CROSS_GLFW_HPP_INCLUDED

