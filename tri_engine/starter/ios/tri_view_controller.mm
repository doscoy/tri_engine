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
    
    
    float native_scale = [UIScreen mainScreen].nativeScale;
    CGRect nativeBounds = [UIScreen mainScreen].nativeBounds;
    float native_x = nativeBounds.size.width * native_scale;
    float native_y = nativeBounds.size.height * native_scale;

        
    // 各機種で内部の座標系を統一する
    screen_scale_ = [UIScreen mainScreen].nativeScale;

    CGRect bounds = [UIScreen mainScreen].bounds;
    screen_x_ = bounds.size.width * screen_scale_;
    screen_y_ = bounds.size.height * screen_scale_;
    auto& framework = t3::Framework::instance();
    
    t3::InitConfiguration config;
    config.window_width_ = screen_x_;
    config.window_height_ = screen_y_;
    
    T3_SYSTEM_LOG("SCREEN SCALE %f  BOUNDS (%d,%d)\n", screen_scale_, (int)bounds.size.width, (int)bounds.size.height );
    T3_SYSTEM_LOG("WINDOW SIZE (%d, %d)\n", (int)screen_x_, (int)screen_y_);


    T3_SYSTEM_LOG("NATIVE SCALE %f  BOUNDS (%d,%d)\n", native_scale, (int)nativeBounds.size.width, (int)nativeBounds.size.height );
    T3_SYSTEM_LOG("WINDOW SIZE (%d, %d)\n", (int)native_x, (int)native_y);


    if (!framework.initializeFramework(config)) {
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
