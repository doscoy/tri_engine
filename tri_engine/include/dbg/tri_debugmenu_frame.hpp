
#ifndef TRI_DEBUGMENU_FRAME_HPP_INCLUDED
#define TRI_DEBUGMENU_FRAME_HPP_INCLUDED

//  include
#include "tri_debugmenu_label.hpp"


namespace t3 {
    
///
/// デバッグメニュー名コンテナ
using DebugMenuList = List<DebugMenuLabel*>;


///
/// デバッグメニュー管理
class DebugMenuFrame 
    : public DebugMenuLabel
{
    //  friends
    friend void DebugMenuLabel::attachSelf(t3::DebugMenuFrame &frame);
    friend void DebugMenuLabel::detachSelf();
    
public:
    ///
    /// コンストラクタ
    DebugMenuFrame(
        DebugMenuFrame* parent, ///< 親
        const String& label     ///< 表示名
    );
    
    ///
    /// デストラクタ
    ~DebugMenuFrame();

public:
    ///
    /// フレームを開く
    void openFrame();
    
    ///
    /// フレームを閉じる
    void closeFrame();
    
    ///
    /// 子要素を持っているか判定
    bool hasChild() const {
        return items_.size() > 0;
    }
    
    ///
    /// フォーカス中のアイテムを取得
    DebugMenuLabel* getFocusItem() {
        return focus_item_;
    }
    
    ///
    /// フォーカス中のアイテムを取得
    const DebugMenuLabel* getFocusItem() const {
        return focus_item_;
    }
    
    ///
    /// フォーカスアイテムを設定
    void setFocusItem(
        DebugMenuLabel* const item
    ){
        if (focus_item_) {
            focus_item_->unfocusCallback();
        }
        if (item) {
            item->focusCallback();
        }
        focus_item_ = item;
    }
    
    ///
    /// アイテムを取得
    DebugMenuList& getItems() {
        return items_;
    }
    
    ///
    /// アイテムを取得
    const DebugMenuList& getItems() const {
        return items_;
    }
    
    ///
    /// 更新
    void update() override;
    
    ///
    /// 描画
    void drawFrame(
        const float x,
        const float y,
        const Color& color
    ) const;
    
    
private:
    ///
    /// アイテムをアタッチ
    void attachItem(DebugMenuLabel& item);
    
    ///
    /// アイテムをデタッチ
    void detachItem(DebugMenuLabel& item);
    
private:
    DebugMenuList items_;           ///< 子アイテム一覧
    DebugMenuLabel* focus_item_;    ///< フォーカス中のアイテム
    int select_idx_;                ///< 選択中のインデックス


};


}   // namespace t3

#endif // TRI_DEBUGMENU_FRAME_HPP_INCLUDED