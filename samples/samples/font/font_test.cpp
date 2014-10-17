

#include "font_test.hpp"
#include "font_texture.hpp"
#include "../shader/tri_font.fsh"
#include "../shader/tri_sprite.vsh"



class FontTestScene::SceneContext {

public:
    SceneContext()
        : layer_()
        , moji_(nullptr)
        , box_(&layer_)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize() {

/*
        const Glyph* glyph = searchGryph("$");
        if (!glyph) {
            glyph = t3::searchGryph("?");
        }
    
        t3::Vec2 left_top(
            glyph->position_.x_ + (glyph->metrics_.x_bearing_ * 2),
            glyph->position_.y_
        );
        t3::Vec2 size(glyph->metrics_.width_, glyph->metrics_.height_);
        
        
        
*/
        auto shader = std::make_shared<t3::Shader>(sprite_vsh, font_fsh);
        layer_.renderer().useCustomShader(shader);
        box_.setText(u8"あいうえお");
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
    t3::TextBox box_;
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
















