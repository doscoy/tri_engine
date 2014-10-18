

#include "font_test.hpp"
#include "font_texture.hpp"
#include "../shader/tri_font.fsh"
#include "../shader/tri_sprite.vsh"



class FontTestScene::SceneContext {

public:
    SceneContext()
        : layer_()
        , glyph_lsit_(
            (t3::Glyph*)GLYPHS,
            GLYPH_NUM,
            "font_texture.png"
        )
        , box1_(&layer_, &glyph_lsit_)
        , box2_(&layer_, &glyph_lsit_)
        , box3_(&layer_, &glyph_lsit_)
        , box4_(&layer_, &glyph_lsit_)
        , box5_(&layer_, &glyph_lsit_)
        , box6_(&layer_, &glyph_lsit_)
    {
    }
    
    ~SceneContext()
    {
    }
  
public:
    void initialize() {
        auto shader = std::make_shared<t3::Shader>(sprite_vsh, font_fsh);
        layer_.renderer().useCustomShader(shader);

        box1_.text(u8"left")
            .center(t3::Vec2(-155, 400))
            .size(t3::Vec2(300, 150))
            .fontsize(32)
            .alignX(t3::TextBox::AlignX::LEFT)
            .alignY(t3::TextBox::AlignY::CENTER)
            .setup();
        
        box2_.text(u8"center")
            .center(t3::Vec2(155, 400))
            .size(t3::Vec2(300, 150))
            .fontsize(32)
            .alignX(t3::TextBox::AlignX::CENTER)
            .alignY(t3::TextBox::AlignY::CENTER)
            .setup();

        
        box3_.text(u8"right")
            .center(t3::Vec2(155,200))
            .size(t3::Vec2(300, 150))
            .alignX(t3::TextBox::AlignX::RIGHT)
            .alignY(t3::TextBox::AlignY::CENTER)
            .setup();

        box4_.text(u8"top")
            .center(t3::Vec2(-155,200))
            .size(t3::Vec2(300, 150))
            .alignX(t3::TextBox::AlignX::CENTER)
            .alignY(t3::TextBox::AlignY::TOP)
            .setup();

        box5_.text(u8"bottom")
            .center(t3::Vec2(-155,0))
            .size(t3::Vec2(300, 150))
            .alignX(t3::TextBox::AlignX::CENTER)
            .alignY(t3::TextBox::AlignY::BOTTOM)
            .setup();

        box6_.text(u8"01234567890")
            .center(t3::Vec2(0,-200))
            .size(t3::Vec2(300, 100))
            .alignX(t3::TextBox::AlignX::CENTER)
            .alignY(t3::TextBox::AlignY::TOP)
            .setup();
    }
    
    void terminate() {

    }
    
    void debugRender() {
        t3::drawRectangleCenterSize(box1_.center(), box1_.size(), t3::Color(255, 113, 45, 128));
        t3::drawRectangleCenterSize(box2_.center(), box2_.size(), t3::Color(255, 113, 45, 128));
        t3::drawRectangleCenterSize(box3_.center(), box3_.size(), t3::Color(255, 113, 45, 128));
        t3::drawRectangleCenterSize(box4_.center(), box4_.size(), t3::Color(255, 113, 145, 128));
        t3::drawRectangleCenterSize(box5_.center(), box5_.size(), t3::Color(255, 113, 145, 128));
        t3::drawRectangleCenterSize(box6_.center(), box6_.size(), t3::Color(255, 113, 145, 128));
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
    t3::GlyphList glyph_lsit_;
    t3::TextBox box1_;
    t3::TextBox box2_;
    t3::TextBox box3_;
    t3::TextBox box4_;
    t3::TextBox box5_;
    t3::TextBox box6_;
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

void FontTestScene::debugRenderScene() {
    context_->debugRender();
}

void FontTestScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















