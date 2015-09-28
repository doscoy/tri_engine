////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_debugmenu_label.hpp
    ラベル付デバッグメニューアイテム.
*/

#ifndef TRI_DEBUGMENU_LABEL_HPP_INCLUDED
#define TRI_DEBUGMENU_LABEL_HPP_INCLUDED


//  include
#include "core/core_config.hpp"
#include "tri_print.hpp"
#include "../utility/tri_util.hpp"
#include <string.h>






TRI_CORE_NS_BEGIN


    
// 前方宣言
class DebugMenuFrame;


///
/// デバッグメニューアイテムの基本クラス.
/// ラベルを持つ
class DebugMenuLabel
    : private Uncopyable
{
    ///
    /// コールバックメソッド
    using callback_t = MethodCallbackX<DebugMenuLabel>;

    ///
    /// コンストラクタ
    DebugMenuLabel();
public:
    ///
    /// コンストラクタ
    DebugMenuLabel(
        DebugMenuFrame* parent,
        const String& label
    );
    
    ///
    /// デストラクタ
    virtual ~DebugMenuLabel();
    

public:
    ///
    /// ラベル取得
    const String& getLabel() const {
        return label_;
    };
    ///
    /// ラベル幅取得
    std::size_t getLabelWidth() const {
        return label_.size();
    };
    
    ///
    /// 親フレームを取得
    DebugMenuFrame* getParent() {
        return parent_;
    }
    
    ///
    /// 親フレームを設定
    void setParent(DebugMenuFrame* parent){
        parent_ = parent;
    }

    ///
    /// 子を持っているか調査
    virtual bool hasChild() const {
        return false;
    }
    
    ///
    /// 自身を親にアタッチ
    void attachSelf(
        DebugMenuFrame& frame   ///< 親
    );
    
    ///
    /// 親から自身をデタッチ
    void detachSelf();
    
    ///
    /// 有効設定
    void enable(const bool enable) {
        enable_ = enable;
    }
    
    ///
    /// 有効判定
    bool enabled() const {
        return enable_;
    }
    
    ///
    /// 更新
    virtual void update(){};

    ///
    /// 描画
    virtual void draw(
        const float x,
        const float y,
        const Color& color
    ) const;

    ///
    /// フォーカス時のコールバックを設定
    template <typename T>
    void setFocusCallback(
        T* owner,
        void (T::*callback)()
    ) {
        MethodCallbackX<T> cb(owner, callback);
        focus_callback_ = (callback_t&)cb;
    }

    
    ///
    /// アンフォーカス時のコールバックを設定
    template <typename T>
    void setUnfocusCallback(
        T* owner,
        void (T::*callback)()
    ) {
        MethodCallbackX<T> cb(owner, callback);
        unfocus_callback_ = (callback_t&)cb;
    }

    ///
    /// フォーカス時のコールバックを呼ぶ
    void focusCallback() {
//        T3_ASSERT(focus_callback_.canInvoke());
        focus_callback_.invoke();
    }
    
    ///
    /// アンフォーカス時のコールバックを呼ぶ
    void unfocusCallback() {
//        T3_ASSERT(unfocus_callback_.canInvoke());
        unfocus_callback_.invoke();
    }

private:
    ///
    /// 何もしない用のコールバック
    void nullCallback() {}
    
protected:
    DebugMenuFrame* parent_; ///< 親フレーム
    String label_;  ///< ラベル
    bool enable_;   ///< 有効フラグ
    
    //  開閉コールバック
    callback_t focus_callback_;     ///< フォーカス時のコールバック
    callback_t unfocus_callback_;   ///< アンフォーカス時のコールバック

};



TRI_CORE_NS_END

#endif // TRI_DEBUGMENU_LABEL_HPP_INCLUDED
