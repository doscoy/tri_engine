

#include "font_test.hpp"
#include "font_texture.hpp"
#include "../shader/tri_font.fsh"
#include "../shader/tri_sprite.vsh"



namespace  {

bool isCompUTF8(
    const char* const a,
    const char* const b
) {

    for (int i = 0; i < 3; ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }


    return true;
}


const Glyph* searchGryph(const char* c) {

    for (int i = 0; i < GLYPHS_SIZE; ++i) {
        const Glyph* glyph = &GLYPHS[i];
        
        if (isCompUTF8(glyph->char_, c)) {
            return glyph;
        }
    }
    return nullptr;
}





}




class FontTestScene::SceneContext {

public:
    SceneContext()
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize() {
        const Glyph* glyph = searchGryph("$");
        if (!glyph) {
            glyph = searchGryph("?");
        }
    
        t3::Vec2 left_top(
            glyph->position_.x_ + (glyph->metrics_.x_bearing_ * 2),
            glyph->position_.y_
        );
        t3::Vec2 size(glyph->metrics_.width_, glyph->metrics_.height_);
        
        moji_ = layer_.createSprite("font_texture.png");
        moji_->setupTextureCoordAndSize(left_top, size);
        moji_->transform()->scale(10.0);
        moji_->color(t3::Color::BLUE);
        
        
        auto shader = std::make_shared<t3::Shader>(sprite_vsh, font_fsh);
        layer_.renderer().useCustomShader(shader);
    }
    
    void terminate() {

    }
    
    void update(t3::tick_t delta_time) {
        T3_PRINT_DISP(40, 50, t3::Color::white(), "aiueo");
        T3_PRINT_DISP(40, 70, t3::Color::lime(), "aiueo");
        T3_PRINT_DISP(40, 90, t3::Color::BLACK, "aiueo");
        T3_PRINT_DISP(40, 110, t3::Color::orange(), "aiueo");
    }


    void suspend(t3::tick_t delta_time) {

    }

private:
    t3::SpriteLayer layer_;
    t3::SpritePtr moji_;
};






FontTestScene::FontTestScene()
    : Scene( "Template" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

FontTestScene::~FontTestScene() {
    
}


void FontTestScene::initializeScene() {
    context_->initialize();
}


void FontTestScene::terminateScene() {
    context_->terminate();
}


void FontTestScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void FontTestScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















