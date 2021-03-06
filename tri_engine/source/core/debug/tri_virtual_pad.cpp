////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/debug/tri_virtual_pad.hpp"
#include "core/debug/tri_draw_primitive.hpp"
#include "core/base/tri_director.hpp"
#include "core/geometry/tri_collision.hpp"
#include "core/geometry/tri_rectangle.hpp"


TRI_CORE_NS_BEGIN


namespace {

const float PAD_Y = -310;
const t3::Vec2 BUTTON_SIZE(64, 64);

const float offset = 64;
const t3::Vec2 CROSS_BASE_POS(-200, PAD_Y);
const t3::Vec2 POS_UP = CROSS_BASE_POS + t3::Vec2(0, offset);
const t3::Vec2 POS_DOWN = CROSS_BASE_POS + t3::Vec2(0, -offset);
const t3::Vec2 POS_LEFT = CROSS_BASE_POS + t3::Vec2(-offset, 0);
const t3::Vec2 POS_RIGHT = CROSS_BASE_POS + t3::Vec2(offset, 0);

const t3::Vec2 AB_BASE = t3::Vec2(100, PAD_Y);
const t3::Vec2 POS_A = AB_BASE + t3::Vec2(0, 0);
const t3::Vec2 POS_B = AB_BASE + t3::Vec2(offset + 32, 0);


const t3::Rectangle UP_BUTTON(POS_UP, POS_UP + BUTTON_SIZE);
const t3::Rectangle DOWN_BUTTON(POS_DOWN, POS_DOWN + BUTTON_SIZE);
const t3::Rectangle LEFT_BUTTON(POS_LEFT, POS_LEFT + BUTTON_SIZE);
const t3::Rectangle RIGHT_BUTTON(POS_RIGHT, POS_RIGHT + BUTTON_SIZE);
const t3::Rectangle A_BUTTON(POS_A, POS_A + BUTTON_SIZE);
const t3::Rectangle B_BUTTON(POS_B, POS_B + BUTTON_SIZE);

}



VirtualPad::VirtualPad()
    : pad_layer_("vpad", LayerBase::Priority::SYS_DEBUG)
{
    pad_layer_.setUpdateCallback<VirtualPad>(this, &VirtualPad::updateVirtualPad);
    pad_layer_.setRenderCallback<VirtualPad>(this, &VirtualPad::renderVirtualPad);
}

VirtualPad::~VirtualPad() {

}


void VirtualPad::open() {
#ifndef DEBUG
    return;
#endif // DEBUG


    pad_layer_.enableLayer();
}

void VirtualPad::close() {
    pad_layer_.disableLayer();
}

void VirtualPad::updateVirtualPad() {

    //  パッドデータクリア
    pad_data_.clearData();


    //  ポインティング情報取得
    auto& director = Director::instance();
    const Input& input = director.input();
    const Pointing& pointing = input.pointing();

    if (!pointing.isHold()) {
        //  触ってない
        return;
    }

    const Vec2& pointing_pos = pointing.position();


    if (isHitPointRectangle(
        pointing_pos,
        UP_BUTTON
    )) {
        //  押してる
        t3::bitOn(pad_data_.button_data_, t3::Pad::BUTTON_UP);
    }


    if (isHitPointRectangle(
        pointing_pos,
        DOWN_BUTTON)) {
        //  押してる
        t3::bitOn(pad_data_.button_data_, t3::Pad::BUTTON_DOWN);
    }


    if (isHitPointRectangle(
        pointing_pos,
        RIGHT_BUTTON)) {
        //  押してる
        t3::bitOn(pad_data_.button_data_, t3::Pad::BUTTON_RIGHT);
    }

    if (isHitPointRectangle(
        pointing_pos,
        LEFT_BUTTON)) {
        //  押してる
        t3::bitOn(pad_data_.button_data_, t3::Pad::BUTTON_LEFT);
    }


    if (isHitPointRectangle(
        pointing_pos,
        A_BUTTON)) {
        //  押してる
        t3::bitOn(pad_data_.button_data_, t3::Pad::BUTTON_A);
    }
    if (isHitPointRectangle(
        pointing_pos,
        B_BUTTON)) {
        //  押してる
        t3::bitOn(pad_data_.button_data_, t3::Pad::BUTTON_B);
    }


}

void VirtualPad::renderVirtualPad() {


    
    //  バーチャルパッド十字キー
    drawRectangleMinSize(
        POS_UP, BUTTON_SIZE, color_sample::lime()
    );
    drawRectangleMinSize(
        POS_DOWN, BUTTON_SIZE, color_sample::lime()
    );
    drawRectangleMinSize(
        POS_RIGHT, BUTTON_SIZE, color_sample::lime()
    );
    drawRectangleMinSize(
        POS_LEFT, BUTTON_SIZE, color_sample::lime()
    );

    //  ABボタン
    drawRectangleMinSize(
        POS_A, BUTTON_SIZE, color_sample::lime()
    );
    drawRectangleMinSize(
        POS_B, BUTTON_SIZE, color_sample::lime()
    );

}



TRI_CORE_NS_END
