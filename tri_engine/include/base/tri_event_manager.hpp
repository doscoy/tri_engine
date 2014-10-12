
#ifndef TRI_EVENT_MANAGER_HPP_INCLUDED
#define TRI_EVENT_MANAGER_HPP_INCLUDED

#include "tri_event.hpp"
#include "util/tri_method_callback.hpp"
#include "base/tri_std.hpp"

namespace t3 {
inline namespace base {
struct EventListen{};

using EventListenerPtr = void*;
using EventHandlerFunction = MethodCallback1<EventListen, const Event&>;
struct EventHandler {
    void* listener_;
    EventHandlerFunction func_;
};
    

#define TRI_DEV_EVENT_TRACE 1


class EventManagerBase
{
public:
    explicit EventManagerBase(
        const char* const name,
        bool set_as_global
    );
    
    virtual ~EventManagerBase();
    
public:
    virtual bool addListener(
        const EventHandler& in_handler,
        const EventType& in_type
    ) = 0;
  
    
    virtual bool removeListener(
        const EventListenerPtr in_handler,
        const EventType& in_type
    ) = 0;
    
    virtual bool removeListener(
        const EventListenerPtr listener
    ) = 0;
    
    
    
    virtual bool queueEvent(
        const EventPtr& in_event
    ) = 0;
    
    virtual bool triggerEvent(
        const EventPtr in_event
    ) = 0;
    
    virtual bool abortEvent(
        const EventType& in_type,
        bool all_type = false
    ) = 0;
    
    virtual bool tick(
        uint32_t max_milli = 999999
    ) = 0;
    
    virtual void dumpListeners() const = 0;
    
    virtual bool isValidateEventType(const EventType& in_type) const = 0;

    static EventManagerBase* get();

private:

    
    friend bool safeAddListener(
        const EventListenerPtr& in_hander,
        const EventType& in_type
    );
    
    friend bool safeRemoveListener(
        const EventListenerPtr in_handler,
        const EventType& in_type
    );
    
    friend bool safeRemoveListener(
        const EventListenerPtr& listener
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
    
bool safeRemoveListener(
    const EventListenerPtr in_handler,
    const EventType& in_type
);

bool safeRemoveListener(
    const EventListenerPtr listener
);
    
    
bool safeQueueEvent(
    const EventPtr& in_event
);

void safeQueueEvent(
    const EventPtr& in_event,
    float delay_sec
);




bool safeAbortEvent(
    const EventType& in_type,
    bool all_type = false
);
    
bool safeTickEventManager(
    uint32_t max_milli = 99999
);
    
bool safeValidateEventType(
    const EventType& in_type
);


void safeTriggerEvent(
    const EventPtr in_event
);




using EventListenerList = Vector<void*>;
using EventTypeList = Vector<EventType>;

class EventManager
    : public EventManagerBase
{
private:
    //  イベントマネージャが処理できる固有のイベント型のセット
    using EventTypeSet = Set<EventType>;
    
    //  EventTypeSetへの挿入結果
    using EventTypeSetInsertResult = std::pair<EventTypeSet::iterator, bool>;
    
    
    //  イベントハンドラのテーブル
    using EventListenerTable = List<EventHandler>;
    
    //  リスナーのリストと特定のイベントの関連付け
    using EventListenerMap = std::map<HashString::key_t, EventListenerTable>;
    
    //  EventListenerMapの検索結果
    using EventListenerMapEntry = std::pair<HashString::key_t, EventListenerTable>;
    
    //  EventListenerMapへの挿入結果
    using EventListenerMapInsertResult = std::pair<EventListenerMap::iterator, bool>;
    
    //  イベントキュー
    using EventQueue = List<EventPtr>;

public:
    explicit EventManager(
        const char* const name,
        bool set_as_global
    );
    
    ~EventManager();
    
public:
    bool addListener(
        const EventHandler& in_handler,
        const EventType& in_type
    ) override;
    
    
    bool removeListener(
        const EventListenerPtr in_handler,
        const EventType& in_type
    ) override;
    
    bool removeListener(
        const EventListenerPtr listener
    ) override;
    
    
    bool queueEvent(
        const EventPtr& in_event
    ) override;
    
    bool abortEvent(
        const EventType& in_type,
        bool all_type = false
    ) override;
    
    bool tick(
        uint32_t proc_limit = 999999
    ) override;
    
    bool triggerEvent(
        const EventPtr in_event
    ) override;
    
    
    bool isValidateEventType(const EventType& in_type) const override;

    EventListenerList getListenerList(
        const EventType& event_type
    ) const;

    EventTypeList getTypeList() const;
    
    void dumpListeners() const;
    String getEventNameByKey(HashString::key_t key) const;
private:
    enum {
        NUM_QUEUES = 2
    };
    
    
    //  登録済のイベントリスト
    EventTypeSet type_list_;
    
    //  イベントとリスナーのマッピング
    EventListenerMap registry_;
    
    //  二重バッファのイベント処理キュー
    EventQueue queues_[NUM_QUEUES];
    
    int active_queue_;

};




}   // namespace base
}   // namespace t3

#endif // TRI_EVENT_MANAGER_HPP_INCLUDED

