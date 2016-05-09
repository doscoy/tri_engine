////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_event_manager.hpp
    イベントマネージャ.
*/
#ifndef TRI_EVENT_MANAGER_HPP_INCLUDED
#define TRI_EVENT_MANAGER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "tri_event.hpp"
#include "core/utility/tri_method_callback.hpp"


TRI_CORE_NS_BEGIN

///
/// イベントレシーバー
struct EventListen{};

///
/// イベントリスナポインタ
using EventListenerPtr = const void*;

using EventHandler = t3::SharedPtr<MethodCallbackBase>;


#define TRI_DEV_EVENT_TRACE 1   ///< イベントのトレースフラグ



using EventListenerList = Vector<EventListenerPtr>;
using EventTypeList = Vector<EventType>;

///
///
class EventManager {
private:
    ///
    /// イベントマネージャが処理できる固有のイベント型のセット
    using EventTypeSet = Set<EventType>;
    
    ///
    ///  EventTypeSetへの挿入結果
    using EventTypeSetInsertResult = std::pair<EventTypeSet::iterator, bool>;
    
    ///
    ///  イベントハンドラのテーブル
    using EventListenerTable = List<EventHandler>;
    
    ///
    ///  リスナーのリストと特定のイベントの関連付け
    using EventListenerMap = std::map<HashString::key_t, EventListenerTable>;
    
    ///
    ///  EventListenerMapの検索結果
    using EventListenerMapEntry = std::pair<HashString::key_t, EventListenerTable>;
    
    ///
    ///  EventListenerMapへの挿入結果
    using EventListenerMapInsertResult = std::pair<EventListenerMap::iterator, bool>;
    
    ///
    ///  イベントキュー
    using EventQueue = List<EventPtr>;

public:
    static void initialize();

    ///
    /// リスナー登録
    static bool addListenerCore(
        const EventHandler& in_handler,
        const EventType& in_type
    );
    
    ///
    /// リスナ追加
    template <typename T>
    static bool addListener(
        const T* listener,
        void (T::*func)(const EventPtr),
        const EventType& in_type
    ) {
        auto handler = std::make_shared<MethodCallback1<T,const EventPtr>>(listener, func);
        return addListenerCore(handler, in_type);
    }
    
    ///
    /// リスナーの削除
    static bool removeListener(
        const EventListenerPtr listener
    );
    
    
    ///
    /// イベントを登録
    static bool queueEvent(
        const EventPtr& in_event
    );
    
    ///
    /// イベント停止
    static bool abortEvent(
        const EventType& in_type,
        bool all_type = false
    );
    
    ///
    /// 更新
    static bool broadCast(const FrameInfo& frame_info);
    
    
    ///
    /// イベントタイプを取得
    static bool isValidateEventType(const EventType& in_type);

    ///
    /// リスナリストを取得
    static EventListenerList getListenerList(
        const EventType& event_type
    );

    ///
    /// イベントタイプリストを取得
    static EventTypeList getTypeList();
    
    ///
    /// リスナ一覧をダンプ
    static void dumpListeners();

    ///
    /// イベント名をキーから取得
    static String getEventNameByKey(HashString::key_t key);


    static void switchQueue();
    
    static EventQueue& currentQueue();
    static EventQueue& backQueue();
    
private:
    
    static EventTypeSet type_list_;        ///< 登録済のイベントリスト
    
    static EventListenerMap registry_;     ///< 登録済のリスナ
    
    static EventQueue queue_[2];           ///< イベントキュー
  
    static int current_queue_id_;
    static int back_queue_id_;
};



TRI_CORE_NS_END

#endif // TRI_EVENT_MANAGER_HPP_INCLUDED

