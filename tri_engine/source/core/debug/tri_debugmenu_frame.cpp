////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/debug/tri_debugmenu_frame.hpp"
#include "core/debug/tri_print.hpp"
#include "core/debug/tri_debugpad.hpp"
#include "core/debug/tri_trace.hpp"

TRI_CORE_NS_BEGIN


    
///
/// コンストラクタ
DebugMenuFrame::DebugMenuFrame(
    DebugMenuFrame* parent,
    const String& label
)   : DebugMenuLabel(parent, label)
    , items_()
    , focus_item_(nullptr)
    , select_idx_(0)
{
}


///
/// デストラクタ
DebugMenuFrame::~DebugMenuFrame()
{
}

///
/// デバッグメニュー項目をひらく
void DebugMenuFrame::openFrame()
{
    for (auto item: items_) {
        item->enable(true);
    }
    
    DebugMenuLabel* focus_item = getFocusItem();
    if (focus_item){
        if (focus_item_->hasChild()){
            DebugMenuFrame* dmf = static_cast<DebugMenuFrame*>(focus_item_);
            dmf->openFrame();
        }
    }
}

///
/// デバッグメニュー項目を閉じる
void DebugMenuFrame::closeFrame()
{
    for (auto item: items_) {
        item->enable(false);
    }
    setFocusItem(nullptr);
}

///
/// このフレームに子アイテムを登録
void DebugMenuFrame::attachItem(
    DebugMenuLabel* item
){
    if (item->getParent()){
        //  既にどこかのFrameに付いている
        //  ので外す
        item->detachSelf();
        
    }
    //  自分を親フレームにする
    item->setParent(this);
    
    //  子リストに追加
    items_.push_back(item);
}

///
/// この項目から子アイテムを削除
void DebugMenuFrame::detachItem(
    DebugMenuLabel* item
){
    //  自分の管理アイテムか判定
    T3_ASSERT(item->getParent() == this);
    if (item == focus_item_) {
        setFocusItem(nullptr);
    }
    //  親を無効化
    item->setParent(nullptr);

    //  子リストから外す
    items_.remove(item);
    
    

}



///
/// 更新
void DebugMenuFrame::update()
{
    DebugMenuLabel* focus = getFocusItem();
    if ( focus ){
        //  この先のメニューにフォーカスが移っている
        focus->update();
    }
    else {
        //  フォーカス項目を移動
        const Pad& pad = debugPad();
        uint32_t items_size = static_cast<uint32_t>(items_.size());
        
        if (pad.isRepeat(t3::Pad::BUTTON_UP)) {
            select_idx_ -= 1;
            if (select_idx_ < 0) {
                select_idx_ = items_size -1;
            }
        }
        else if (pad.isRepeat(t3::Pad::BUTTON_DOWN)) {
            select_idx_ += 1;
            if (select_idx_ >= items_size) {
                select_idx_ = 0;
            }
        }
        else if (pad.isTrigger(t3::Pad::BUTTON_A)) {
            //  フォーカスする
            int idx = 0;
            for (auto item: items_){
                if (select_idx_ == idx){
                    setFocusItem(item);
                    break;
                }
                ++idx;
            }
        }
        else if (pad.isTrigger(t3::Pad::BUTTON_B)) {
            //  フォーカスを外す
            if (parent_) {
                parent_->setFocusItem(nullptr);
            }
        }
        
    }

}
    
///
/// フレームを描画する
void DebugMenuFrame::drawFrame(
    const float x,
    const float y,
    const Color& color
) const {

    //  描画
    printDisplay(x, y, color, TRI_DEBUG_FONT_SIZE, getLabel().c_str());

    int idx = 0;
    Color font_color;
    for (auto item: items_) {
        T3_NULL_ASSERT(item);

        if (focus_item_ == item) {
            font_color = color_sample::orange();
        }
        else if (idx == select_idx_) {
            font_color = color_sample::cyan();
        }
        else {
            font_color = color_sample::white();
        }
        
        //
        if (focus_item_ == item && item->hasChild()) {
            //  フレームなのでさらにフレームの内容を描画
            DebugMenuFrame* dmf = static_cast<DebugMenuFrame*>(item);
            dmf->drawFrame(
                x + getLabelWidth() * TRI_DEBUG_FONT_SIZE,
                y + (idx * TRI_DEBUG_FONT_SIZE) + TRI_DEBUG_FONT_SIZE / 2,
                font_color
            );
        }
        else {
            //  アイテムを描画
            item->draw(
                x + getLabelWidth() * TRI_DEBUG_FONT_SIZE,
                y + (TRI_DEBUG_FONT_SIZE*idx) + TRI_DEBUG_FONT_SIZE / 2,
                font_color
            );
        }        
        
        idx += 1;
    }
}


TRI_CORE_NS_END

