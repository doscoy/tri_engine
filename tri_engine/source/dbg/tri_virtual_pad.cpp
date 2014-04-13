#include "tri_virtual_pad.hpp"
#include "tri_draw_primitive.hpp"
#include "base/tri_game_system.hpp"
#include "geometry/tri_collision.hpp"



namespace {
    
const t3::Vec2 BUTTON_SIZE(64, 64);

const float offset = 64;
const t3::Vec2 CROSS_BASE_POS(100, 800);
const t3::Vec2 POS_UP = CROSS_BASE_POS + t3::Vec2(0, -offset);
const t3::Vec2 POS_DOWN = CROSS_BASE_POS + t3::Vec2(0, offset);
const t3::Vec2 POS_LEFT = CROSS_BASE_POS + t3::Vec2(-offset, 0);
const t3::Vec2 POS_RIGHT = CROSS_BASE_POS + t3::Vec2(offset, 0);

const t3::Vec2 AB_BASE = t3::Vec2(400, 800);
const t3::Vec2 POS_A = AB_BASE + t3::Vec2(0, 0);
const t3::Vec2 POS_B = AB_BASE + t3::Vec2(offset + 32, 0);

}



namespace t3 {
inline namespace dbg {

VirtualPad::VirtualPad()
    : pad_layer_()
{
    pad_layer_.setLayerName("virtual pad");
    pad_layer_.setUpdateCallback(this, &VirtualPad::updateVirtualPad);
    pad_layer_.setRenderCallback(this, &VirtualPad::renderVirtualPad);

    pad_layer_.attachSystem();
}

VirtualPad::~VirtualPad() {
    pad_layer_.detachSystem();
}


void VirtualPad::open() {
    pad_layer_.enableLayer();
}

void VirtualPad::close() {
    pad_layer_.disableLayer();
}

void VirtualPad::updateVirtualPad(t3::DrawLayer* const layer, tick_t delta_time) {

    //  パッドデータクリア
    pad_data_.clearData();


    //  ポインティング情報取得
    const Input& input = GameSystem::getInput();
    const Pointing& pointing = input.getPointing();

    if (!pointing.isHold()) {
        //  触ってない
        return;
    }

    const Vec2& pointing_pos = pointing.getPosition();


    if (isHitPointAABB(
        pointing_pos,
        POS_UP,
        BUTTON_SIZE)) {
        //  押してる
        t3::bitOn(pad_data_.button_data_, t3::Pad::BUTTON_UP);
    }


    if (isHitPointAABB(
        pointing_pos,
        POS_DOWN,
        BUTTON_SIZE)) {
        //  押してる
        t3::bitOn(pad_data_.button_data_, t3::Pad::BUTTON_DOWN);
    }


    if (isHitPointAABB(
        pointing_pos,
        POS_RIGHT,
        BUTTON_SIZE)) {
        //  押してる
        t3::bitOn(pad_data_.button_data_, t3::Pad::BUTTON_RIGHT);
    }

    if (isHitPointAABB(
        pointing_pos,
        POS_LEFT,
        BUTTON_SIZE)) {
        //  押してる
        t3::bitOn(pad_data_.button_data_, t3::Pad::BUTTON_LEFT);
    }


    if (isHitPointAABB(
        pointing_pos,
        POS_A,
        BUTTON_SIZE)) {
        //  押してる
        t3::bitOn(pad_data_.button_data_, t3::Pad::BUTTON_A);
    }
    if (isHitPointAABB(
        pointing_pos,
        POS_B,
        BUTTON_SIZE)) {
        //  押してる
        t3::bitOn(pad_data_.button_data_, t3::Pad::BUTTON_B);
    }


}

void VirtualPad::renderVirtualPad(t3::DrawLayer* const layer) {


    
    //  バーチャルパッド十字キー
    drawRectangle(
        POS_UP, BUTTON_SIZE, Color::lime()
    );
    drawRectangle(
        POS_DOWN, BUTTON_SIZE, Color::lime()
    );
    drawRectangle(
        POS_RIGHT, BUTTON_SIZE, Color::lime()
    );
    drawRectangle(
        POS_LEFT, BUTTON_SIZE, Color::lime()
    );

    //  ABボタン
    drawRectangle(
        POS_A, BUTTON_SIZE, Color::lime()
    );
    drawRectangle(
        POS_B, BUTTON_SIZE, Color::lime()
    );

}





}   // inline namespace dbg
}   // namespace t3