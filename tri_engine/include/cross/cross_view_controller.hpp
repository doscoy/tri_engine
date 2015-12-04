////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file cross_view_controller.hpp
    iOS開発専用でViewControllerに書く各種設定をラップしてある.
*/

#define ES1_GL_H_GUARD
#define ES1_GLEXT_H_GUARD

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>


@interface CrossViewController : GLKViewController

-(void) setFPS:(int)fps;

@end
