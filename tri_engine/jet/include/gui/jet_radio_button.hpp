/**
    @file jet_radio_button.hpp
    ラジオボタン.
*/

#ifndef JET_RADIO_BUTTON_HPP_INCLUDED
#define JET_RADIO_BUTTON_HPP_INCLUDED

// include
#include "jet_config.hpp"
#include "jet_button.hpp"

TRI_JET_NS_BEGIN


///
///  ラジオボタンに登録されているボタンが押された時のイベント
class RadioButtonEvent
    : public EventBase {

    ///
    /// コンストラクタ
    RadioButtonEvent();
public:
    ///
    /// デストラクタ
    RadioButtonEvent(
        const UniqueID group_id,
        const UniqueID button_id,
        int button_idx
    )   : button_id_(button_id)
        , group_id_(group_id)
        , button_index_(button_idx) {
    }
    
    ///
    /// イベント種別
    static const EventType TYPE;

    ///
    /// イベントタイプ取得
    const EventType& eventType() const override {
        return TYPE;
    }
    
    ///
    /// ボタンID取得
    UniqueID buttonID() const {
        return button_id_;
    }
    
    ///
    /// グループID取得
    UniqueID groupID() const {
        return group_id_;
    }
    
    ///
    /// ボタンのインデックス取得
    int buttonIndex() const {
        return button_index_;
    }
    
private:
    UniqueID button_id_;    ///< ボタン番号
    UniqueID group_id_;     ///< グループ番号
    int button_index_;      ///< グループ内でのボタンインデックス
};



//  ラジオボタン
class RadioButton {
public:
    ///
    /// コンストラクタ
    RadioButton();
    
    ///
    /// デストラクタ
    ~RadioButton();
    
public:
    ///
    /// ボタン登録
    void registryButton(
        Button* button
    );

    ///
    /// 有効なボタンのインデックス取得
    int activeButtonIndex() const {
        return active_button_idx_;
    }
    
    ///
    /// 有効なボタンのID取得
    UniqueID activeButtonID() const {
        return buttons_[active_button_idx_]->buttonID();
    }

    ///
    /// グループID取得
    UniqueID id() {
        return group_id_;
    }

private:
    ///
    /// ラジオボタンが変更された時に呼ばれる関数
    void onRadioButtonTriggered(
        const EventPtr event
    );

private:
    Vector<Button*> buttons_;   ///< 登録されているボタン群
    UniqueID group_id_;         ///< ラジオボタンのグループID
    int active_button_idx_;     ///< アクティブなボタンのインデックス
};




TRI_JET_NS_END



#endif  // JET_RADIO_BUTTON_HPP_INCLUDED

