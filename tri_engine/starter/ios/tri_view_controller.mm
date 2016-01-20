////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#import "tri_view_controller.hpp"
#import "tri_engine.hpp"



extern float screen_scale_;
extern float screen_x_;
extern float screen_y_;

@interface TriViewController () {

}

@end

@implementation TriViewController


- (void)viewDidLoad
{

    [super viewDidLoad];
    
        
    // 各機種で内部の座標系を統一する
    screen_scale_ = [UIScreen mainScreen].scale;

    CGRect bounds = [UIScreen mainScreen].bounds;
    screen_x_ = bounds.size.width * screen_scale_;
    screen_y_ = bounds.size.height * screen_scale_;
    auto& framework = t3::Framework::instance();
    if (!framework.initializeFramework(screen_x_, screen_y_, "ios")) {
        T3_PANIC("initialize failed");
    }
    T3_RENDER_ASSERT();

}



- (void)dealloc {
    auto& framework = t3::Framework::instance();
    framework.terminateFramework();
}




#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    T3_RENDER_ASSERT();
    auto& framework = t3::Framework::instance();
    framework.updateFramework();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    auto& framework = t3::Framework::instance();
    framework.renderFramework();
}

#pragma mark -  OpenGL ES 2 shader compilation



@end
