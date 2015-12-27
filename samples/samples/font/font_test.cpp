////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "font_test.hpp"
#include "font_texture.hpp"
#include "shader/tri_font.fsh"
#include "shader/tri_df_font.fsh"
#include "shader/tri_sprite.vsh"



class FontTestScene::SceneContext {

public:
    SceneContext()
        : layer_()
        , df_layer_()
        , glyph_list_(
            (t3::Glyph*)GLYPHS,
            GLYPH_NUM,
            "font_texture.png",
            FONT_SIZE
        )
        , df1_glyph_list_(
            (t3::Glyph*)GLYPHS,
            GLYPH_NUM,
            "distance_font.png",
            FONT_SIZE
        )
        , df2_glyph_list_(
            (t3::Glyph*)GLYPHS,
            GLYPH_NUM,
            "distance_font.png",
            FONT_SIZE
        )
        , box1_(&layer_, &glyph_list_)
        , box2_(&layer_, &glyph_list_)
        , box3_(&layer_, &glyph_list_)
        , box4_(&layer_, &glyph_list_)
        , box5_(&layer_, &glyph_list_)
        , box6_(&layer_, &glyph_list_)
        , box_df1_(&layer_, &glyph_list_)
        , box_df2_(&df_layer_, &glyph_list_)
    {
    }
    
    ~SceneContext()
    {
    }
  
public:
    void initialize() {
        auto shader = t3::Shader::create(sprite_vsh, font_fsh);
        layer_.renderer().useCustomShader(shader);

        box1_.text(u8"left")
            .center(t3::Vec2(-155, 400))
            .size(t3::Vec2(300, 150))
            .alignX(t3::TextBox::AlignX::LEFT)
            .alignY(t3::TextBox::AlignY::CENTER)
            .setup();
        
        box2_.text(u8"center")
            .center(t3::Vec2(155, 400))
            .size(t3::Vec2(300, 150))
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

    const char* box_text = u8"top";

        box6_.text(box_text)
            .center(t3::Vec2(0,-240))
            .size(t3::Vec2(300, 100))
            .fontSize(32)
            .alignX(t3::TextBox::AlignX::CENTER)
            .alignY(t3::TextBox::AlignY::CENTER)
            .setup();
        
        
        
        auto df_shader = t3::Shader::create(sprite_vsh, df_font_fsh);
     //   layer_.renderer().useCustomShader(df_shader);
        df_layer_.renderer().useCustomShader(df_shader);

        box_df1_.text(box_text)
            .center(t3::Vec2(0,200))
            .size(t3::Vec2(300, 100))
            .alignX(t3::TextBox::AlignX::CENTER)
            .fontSize(96)
            .alignY(t3::TextBox::AlignY::CENTER)
            .setup();

        box_df2_.text(box_text)
            .center(t3::Vec2(0,-200))
            .size(t3::Vec2(300, 100))
            .alignX(t3::TextBox::AlignX::CENTER)
            .fontSize(96)
            .alignY(t3::TextBox::AlignY::CENTER)
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
        t3::drawRectangleCenterSize(box6_.center(), box6_.size(), t3::Color(205, 13, 195, 100));
        t3::drawRectangleCenterSize(box_df1_.center(), box_df1_.size(), t3::Color(205, 13, 195, 100));
        t3::drawRectangleCenterSize(box_df2_.center(), box_df2_.size(), t3::Color(205, 13, 195, 100));
    }
    
    void update(t3::DeltaTime delta_time) {
    
    }


private:
    t3::SpriteLayer layer_;
    t3::SpriteLayer df_layer_;
    t3::GlyphList glyph_list_;
    t3::GlyphList df1_glyph_list_;
    t3::GlyphList df2_glyph_list_;
    t3::TextBox box1_;
    t3::TextBox box2_;
    t3::TextBox box3_;
    t3::TextBox box4_;
    t3::TextBox box5_;
    t3::TextBox box6_;
    t3::TextBox box_df1_;
    t3::TextBox box_df2_;
};






FontTestScene::FontTestScene()
    : SceneBase( "Template" ) {
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


void FontTestScene::updateScene(t3::DeltaTime delta_time) {
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















