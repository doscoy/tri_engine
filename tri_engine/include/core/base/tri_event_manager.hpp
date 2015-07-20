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
#include "core/base/tri_std.hpp"

TRI_CORE_NS_BEGIN

///
/// イベントレシーバー
struct EventListen{};

///
/// イベントリスナポインタ
using EventListenerPtr = const void*;

using EventHandler = t3::SharedPtr<MethodCallbackBaseX>;


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
        auto handler = std::make_shared<MethodCallbackX1<T,const EventPtr>>(listener, func);
        return addListenerCore(handler, in_type);
    }


    
    ///
    /// リスナーの削除
    static bool removeListener(
        const EventListenerPtr in_handler,
        const EventType& in_type
    );
    
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
    /// イベント登録
    static void queueEvent(
        const EventPtr& in_event,
        float delay_sec
    );

    
    ///
    /// イベント停止
    static bool abortEvent(
        const EventType& in_type,
        bool all_type = false
    );
    
    ///
    /// 更新
    static bool broadCast();
    
    
    ///
    /// イベントタイプを取得
    static bool isValidateEventType(const EventType& in_type);

    ///
    /// リスナーリストを取得
    static EventListenerList getListenerList(
        const EventType& event_type
    );

    ///
    /// タイプリストを取得
    static EventTypeList getTypeList();
    
    ///
    /// リスナー一覧をダンプ
    static void dumpListeners();

    ///
    /// イベント名をキーから取得
    static String getEventNameByKey(HashString::key_t key);
private:
    
    static EventTypeSet type_list_;        ///< 登録済のイベントリスト
    
    static EventListenerMap registry_;     ///< 登録済のリスナ
    
    static EventQueue queue_;               ///< イベントキュー
  
};



TRI_CORE_NS_END

#endif // TRI_EVENT_MANAGER_HPP_INCLUDED

