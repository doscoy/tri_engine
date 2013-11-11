
#include "tri_develop_base.hpp"
#include "tri_debugmenu_frame.hpp"
#include "tri_print.hpp"
#include "tri_debugpad.hpp"


namespace t3 {
inline namespace dbg {
    

DebugMenuFrame::DebugMenuFrame(
    DebugMenuFrame* parent,
    const char* const label
)   : DebugMenuLabel(parent, label)
    , focus_item_(nullptr)
    , select_idx_(0)
{
    
}


DebugMenuFrame::~DebugMenuFrame()
{

}


void DebugMenuFrame::openFrame()
{
    for (auto item: items_) {
        item->setEnable(true);
    }
    
    DebugMenuLabel* focus_item = getFocusItem();
    if (focus_item){
        if (focus_item_->hasChild()){
            DebugMenuFrame* dmf = static_cast<DebugMenuFrame*>(focus_item_);
            dmf->openFrame();
        }
    }
}


void DebugMenuFrame::closeFrame()
{
    for ( auto item: items_ ) {
        item->setEnable( false );
    }
    setFocusItem(nullptr);
}


void DebugMenuFrame::attachItem(
    DebugMenuLabel& item
){
    if ( item.getParent() ){
        //  既にどこかのFrameに付いている
        //  ので外す
        item.detachSelf();
        
    }
    //  自分を親フレームにする
    item.setParent( this );
    
    //  子リストに追加
    items_.push_back( &item );
}


void DebugMenuFrame::detachItem(
    DebugMenuLabel& item
){
    //  自分の管理アイテムか判定
    T3_ASSERT( item.getParent() == this );

    //  親を無効化
    item.setParent( nullptr );

    //  子リストから外す
    items_.remove( &item );
    

}




void DebugMenuFrame::update()
{
    DebugMenuLabel* focus = getFocusItem();
    if ( focus ){
        //  この先のメニューにフォーカスが移っている
        focus->update();
    }
    else {
        const Pad& pad = debugPad();
        uint32_t items_size = static_cast<uint32_t>(items_.size());
        
        if ( pad.isRepeat( t3::Pad::BUTTON_UP ) ){
            select_idx_ -= 1;
            if ( select_idx_ < 0 ){
                select_idx_ = items_size -1;
            }
        }
        else if ( pad.isRepeat( t3::Pad::BUTTON_DOWN ) ){
            select_idx_ += 1;
            if ( select_idx_ >= items_size ){
                select_idx_ = 0;
            }
        }
        else if (pad.isTrigger( t3::Pad::BUTTON_RIGHT)){
            int idx = 0;
            for (auto item: items_){
                if (select_idx_ == idx){
                    setFocusItem(item);
                    break;
                }
                ++idx;
            }
        }
        else if (pad.isTrigger( t3::Pad::BUTTON_LEFT)){
            if (parent_){
                parent_->setFocusItem(nullptr);
            }
        }
        
    }

}
    

void DebugMenuFrame::drawFrame(
    const float x,
    const float y,
    const Color& color
) const {

    
    printDisplay( x, y, color, getLabel() );

    int idx = 0;
    Color font_color;
    for ( auto item: items_ ) {
        if ( focus_item_ == item ){
            font_color = Color::orange();
        }
        else if ( idx == select_idx_ ) {
            font_color = Color::aqua();
        }
        else {
            font_color = Color::white();
        }
        
        //
        if ( focus_item_ == item && item->hasChild() ) {
            //  フレームなのでさらにフレームの内容を描画
            DebugMenuFrame* dmf = static_cast<DebugMenuFrame*>( item );
            dmf->drawFrame(
                x + getLabelWidth() * DEBUG_FONT_POINT,
                y + ( idx * DEBUG_FONT_POINT ) + DEBUG_FONT_POINT / 2,
                font_color
            );
        }
        else {
            //  アイテムを描画
            item->draw(
                x + getLabelWidth() * DEBUG_FONT_POINT,
                y + (DEBUG_FONT_POINT*idx) + DEBUG_FONT_POINT / 2,
                font_color
            );
        }
        
        
        idx += 1;
    }
    
    
    
}

}   // inline namespace dbg
}   // namespace t3
