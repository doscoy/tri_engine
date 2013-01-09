
#include "tri_develop_base.hpp"
#include "tri_debugmenu_frame.hpp"
#include "tri_print.hpp"
#include "tri_debugpad.hpp"


namespace t3 {
inline namespace dbg {
    

DebugMenuFrame::DebugMenuFrame(
    DebugMenuFrame* parent,
    const char* const label
)   : DebugMenuLabel( parent, label )
    , focus_item_( nullptr )
    , select_idx_( 0 )
{
    
}


DebugMenuFrame::~DebugMenuFrame()
{
    
    
}


void DebugMenuFrame::show()
{
    for ( auto item: items_ ) {
        item->setEnable( true );
    }
    
    DebugMenuLabel* focus_item = getFocusItem();
    if ( focus_item ){
        if ( focus_item_->hasChild() ){
            DebugMenuFrame* dmf = static_cast<DebugMenuFrame*>( focus_item_ );
            dmf->show();
        }
    }
}


void DebugMenuFrame::hide()
{
    for ( auto item: items_ ) {
        item->setEnable( false );
    }
    focus_item_ = nullptr;
}


void DebugMenuFrame::attachItem(
    DebugMenuLabel& item
){
    if ( item.getParent() ){
        //  既にどこかのFrameに付いている
        //  ので外す
        item.dettachSelf();
        
    }
    //  自分を親フレームにする
    item.setParent( this );
    
    //  子リストに追加
    items_.push_back( &item );
}


void DebugMenuFrame::dettachItem(
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
        u_int items_size = items_.size();
        
        if ( pad.isTrigger( t3::PAD_BUTTON_UP ) ){
            select_idx_ -= 1;
            if ( select_idx_ < 0 ){
                select_idx_ = items_size -1;
            }
        }
        else if ( pad.isTrigger( t3::PAD_BUTTON_DOWN ) ){
            select_idx_ += 1;
            if ( select_idx_ >= items_size ){
                select_idx_ = 0;
            }
        }
        else if ( pad.isTrigger( t3::PAD_BUTTON_RIGHT ) ){
            int idx = 0;
            for ( auto item: items_ ){
                if ( select_idx_ == idx ){
                    focus_item_ = item;
                    break;
                }
                ++idx;
            }
        }
        else if ( pad.isTrigger( t3::PAD_BUTTON_LEFT ) ){
            if ( parent_ ){
                parent_->focus_item_ = nullptr;
            }
        }
        
    }

}
    

void DebugMenuFrame::drawFrame(
    const float x,
    const float y
) const {

    setDebugFontSize( DEBUG_FONT_POINT );
    setDebugFontColor( COLOR_RED );
    printDisplay( x, y, getLabel() );

    int idx = 0;
    for ( auto item: items_ ) {
        if ( idx == select_idx_ ) {
            setDebugFontSize( DEBUG_FONT_POINT );
            setDebugFontColor( COLOR_RED );
            
        }
        else {
            setDebugFontSize( DEBUG_FONT_POINT );
            setDebugFontColor( COLOR_WHITE );
        }
        
        
        if ( focus_item_ == item ){
            //  フォーカスがあるアイテムなので強調する
            if ( item->hasChild() ) {
                //  フレームなのでさらにフレームの内容を描画
                DebugMenuFrame* dmf = static_cast<DebugMenuFrame*>( item );
                dmf->drawFrame( x + getLabelWidth()*DEBUG_FONT_POINT, y+(idx*DEBUG_FONT_POINT)+DEBUG_FONT_POINT/2 );
            }
            else {
                //  アイテムを描画
                setDebugFontSize( DEBUG_FONT_POINT );
                setDebugFontColor( COLOR_YELLOW );
                item->draw( x + getLabelWidth()*DEBUG_FONT_POINT, y+(DEBUG_FONT_POINT*idx)+DEBUG_FONT_POINT/2 );
            }
        }
        else {
            //  フォーカスの無いものは普通に描画
            item->draw( x + getLabelWidth()*DEBUG_FONT_POINT, y+(DEBUG_FONT_POINT*idx)+DEBUG_FONT_POINT/2 );
        }
        idx += 1;
    }
    
    
    
}

}   // inline namespace dbg
}   // namespace t3
