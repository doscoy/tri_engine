
#ifndef TRI_EVENT_MANAGER_HPP_INCLUDED
#define TRI_EVENT_MANAGER_HPP_INCLUDED

//  include
#include "tri_event.hpp"
#include "util/tri_method_callback.hpp"
#include "base/tri_std.hpp"

namespace t3 {

///
/// イベントレシーバー
struct EventListen{};

///
/// イベントリスナポインタ
using EventListenerPtr = void*;

///
/// イベントハンドラのコールバック
using EventHandlerFunction = MethodCallback1<EventListen, const Event&>;


///
/// イベントハンドラ
struct EventHandler {
    void* listener_;            ///< リスナ
    EventHandlerFunction func_; ///< コールバック
};
    


#define TRI_DEV_EVENT_TRACE 1   ///< イベントのトレースフラグ


///
/// イベントマネージャベース
class EventManagerBase {
public:
    ///
    /// コンストラクタ
    explicit EventManagerBase(
        const char* const name,
        bool set_as_global
    );
    
    ///
    /// デストラクタ
    virtual ~EventManagerBase();
    
public:
    ///
    /// リスナ登録
    virtual bool addListener(
        const EventHandler& in_handler,
        const EventType& in_type
    ) = 0;
  
    
    ///
    /// リスナ削除
    virtual bool removeListener(
        const EventListenerPtr in_handler,
        const EventType& in_type
    ) = 0;
    
    ///
    /// リスナ削除
    virtual bool removeListener(
        const EventListenerPtr listener
    ) = 0;
    
    
    
    ///
    /// イベント登録
    virtual bool queueEvent(
        const EventPtr& in_event
    ) = 0;
    
    ///
    /// イベント通知
    virtual bool triggerEvent(
        const EventPtr in_event
    ) = 0;
    
    ///
    /// イベント停止
    virtual bool abortEvent(
        const EventType& in_type,
        bool all_type = false
    ) = 0;
    
    ///
    /// 更新
    virtual bool tick(
        uint32_t max_milli = 999999
    ) = 0;
    
    ///
    /// リスナを一覧表示
    virtual void dumpListeners() const = 0;
    
    ///
    /// イベントを有効化
    virtual bool isValidateEventType(const EventType& in_type) const = 0;

    ///
    /// イベントマネージャのインスタンス取得
    static EventManagerBase* get();


private:

    //  friends
    friend bool safeAddListener(
        const EventListenerPtr& in_hander,
        const EventType& in_type
    );
    
    friend bool safeRemoveListener(
        const EventListenerPtr in_handler,
        const EventType& in_type
    );
    
    template <class T>
    friend bool safeRemoveListener(
        const T* listener
    );

    friend bool safeQueueEvent(
        const EventPtr& in_event
    );
    
    
    friend bool safeAbortEvent(
        const EventType& in_type,
        bool all_type
    );
    
    friend bool safeTickEventManager(
       uint32_t max_milli
    );
    
 
    friend bool safeValidateEventType(
        const EventType& in_type
    );



};


///
/// リスナ追加
template <typename T>
bool safeAddListener(
    const T* listener,
    void (T::*func)(const Event&),
    const EventType& in_type
) {
    MethodCallback1<T, const Event&> callback((T*)listener, func);

    EventHandler handler;
    handler.listener_ = (EventListenerPtr)listener;
    handler.func_ = (EventHandlerFunction&)callback;

    T3_ASSERT(EventManagerBase::get());
    return EventManagerBase::get()->addListener(handler, in_type);
}
    
///
/// リスナ削除
bool safeRemoveListener(
    const EventListenerPtr in_handler,
    const EventType& in_type
);

///
/// リスナ削除
bool safeRemoveListener(
    const EventListenerPtr listener
);
    
    
///
/// イベント登録
bool safeQueueEvent(
    const EventPtr& in_event
);

///
/// イベント登録
void safeQueueEvent(
    const EventPtr& in_event,
    float delay_sec
);




///
/// イベントの停止
bool safeAbortEvent(
    const EventType& in_type,
    bool all_type = false
);
    
///
/// イベント通知
bool safeTickEventManager(
    uint32_t max_milli = 99999
);
    
///
/// イベントタイプを有効化
bool safeValidateEventType(
    const EventType& in_type
);


///
/// イベント発動
void safeTriggerEvent(
    const EventPtr in_event
);




using EventListenerList = Vector<void*>;
using EventTypeList = Vector<EventType>;

///
///
class EventManager
    : public EventManagerBase
{
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
    /// コンストラクタ
    explicit EventManager(
        const char* const name,
        bool set_as_global
    );
    
    ///
    /// デストラクタ
    ~EventManager();
    
public:
    ///
    /// リスナー登録
    bool addListener(
        const EventHandler& in_handler,
        const EventType& in_type
    ) override;
    
    
    ///
    /// リスナーの削除
    bool removeListener(
        const EventListenerPtr in_handler,
        const EventType& in_type
    ) override;
    
    ///
    /// リスナーの削除
    bool removeListener(
        const EventListenerPtr listener
    ) override;
    
    
    ///
    /// イベントを登録
    bool queueEvent(
        const EventPtr& in_event
    ) override;
    
    ///
    /// イベント停止
    bool abortEvent(
        const EventType& in_type,
        bool all_type = false
    ) override;
    
    ///
    /// 更新
    bool tick(
        uint32_t proc_limit = 999999
    ) override;
    
    ///
    /// イベント実行
    bool triggerEvent(
        const EventPtr in_event
    ) override;
    
    
    ///
    /// イベントタイプを取得
    bool isValidateEventType(const EventType& in_type) const override;

    ///
    /// リスナーリストを取得
    EventListenerList getListenerList(
        const EventType& event_type
    ) const;

    ///
    /// タイプリストを取得
    EventTypeList getTypeList() const;
    
    ///
    /// リスナー一覧をダンプ
    void dumpListeners() const;

    ///
    /// イベント名をキーから取得
    String getEventNameByKey(HashString::key_t key) const;
private:
    enum {
        NUM_QUEUES = 2  ///< キューの数
    };
    
    
    EventTypeSet type_list_;        ///< 登録済のイベントリスト
    
    EventListenerMap registry_;     ///< 登録済のリスナ
    
    EventQueue queues_[NUM_QUEUES]; ///< 二重バッファのイベントキュー
    
    int active_queue_;              ///< アクティブなキューの番号

};


///
/// リスナの削除
template <class T>
bool safeRemoveListener(
	const T* listener       ///< リスナ
) {
	T3_NULL_ASSERT(listener);
	T3_ASSERT(EventManagerBase::get());
    

    //  リスナ削除    
	return EventManagerBase::get()->removeListener(
		(const t3::EventListenerPtr)listener
	);
}


}   // namespace t3

#endif // TRI_EVENT_MANAGER_HPP_INCLUDED

