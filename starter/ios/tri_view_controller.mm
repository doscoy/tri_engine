
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
    
    t3::initializeTriEngine(screen_x_, screen_y_, "ios");
    t3::initializeApplication();

}



- (void)dealloc {
    t3::terminateApplication();
}




#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    t3::updateApplication();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    t3::renderApplication();
}

#pragma mark -  OpenGL ES 2 shader compilation



@end
