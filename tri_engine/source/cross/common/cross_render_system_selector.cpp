////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "cross/cross_define.hpp"

//  GLバージョンは定義されているか？
#ifndef CROSS_GL_VERSION
#error "CROSS_GL_VERSION undefined. check cross_define.hpp"
#endif

#if CROSS_GL_VERSION == CROSS_GL_40

    #include "cross_render_system_gl4.cpp"

#elif CROSS_GL_VERSION == CROSS_GL_ES2

    #include "cross_render_system_gles2.cpp"

#elif CROSS_GL_VERSION == CROSS_GL_ES3

    #include "cross_render_system_gles3.cpp"

#else

    #error "Unknowen Platform"

#endif
