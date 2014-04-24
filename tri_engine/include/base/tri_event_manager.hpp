
#ifndef TRI_EVENT_MANAGER_HPP_INCLUDED
#define TRI_EVENT_MANAGER_HPP_INCLUDED

#include "tri_event_listener.hpp"
#include <vector>
#include <set>
#include <list>
#include <map>

namespace t3 {
inline namespace base {

using EventListenerPtr = EventListener*;


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
        const EventListenerPtr& in_handler,
        const EventType& in_type
    ) = 0;
  
    
    virtual bool removeListener(
        const EventListenerPtr& in_handler,
        const EventType& in_type
    ) = 0;
    
    virtual bool removeListener(
        const EventListenerPtr& listener
    ) = 0;
    
    virtual bool triggerEvent(
        const EventHandle& in_event
    ) = 0;
    
    virtual bool queueEvent(
        const EventHandle& in_event
    ) = 0;
    
    virtual bool abortEvent(
        const EventType& in_type,
        bool all_type = false
    ) = 0;
    
    virtual bool tick(
        uint32_t max_milli = 999999
    ) = 0;
    
    
    virtual bool isValidateEventType(const EventType& in_type) const = 0;


private:

    static EventManagerBase* get();
    
    friend bool safeAddListener(
        const EventListenerPtr& in_hander,
        const EventType& in_type
    );
    
    friend bool safeRemoveListener(
        const EventListenerPtr& in_handler,
        const EventType& in_type
    );
    
    friend bool safeRemoveListener(
        const EventListenerPtr& listener
    );

    friend bool safeTriggerEvent(
        const EventHandle& in_event
    );
    
    friend bool safeQueueEvent(
        const EventHandle& in_event
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


    
bool safeAddListener(
    const EventListenerPtr& in_hander,
    const EventType& in_type
);
    
bool safeRemoveListener(
    const EventListenerPtr& in_handler,
    const EventType& in_type
);

bool safeRemoveListener(
    const EventListenerPtr& listener
);
    
bool safeTriggerEvent(
    const EventHandle& in_event
);
    
bool safeQueueEvent(
    const EventHandle& in_event
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





using EventListenerList = std::vector<EventListenerPtr>;
using EventTypeList = std::vector<EventType>;

class EventManager
    : public EventManagerBase
{
private:
    //  イベントマネージャが処理できる固有のイベント型のセット
    using EventTypeSet = std::set<EventType>;
    
    //  EventTypeSetへの挿入結果
    using EventTypeSetInsertResult = std::pair<EventTypeSet::iterator, bool>;
    
    //  イベントリスナーのテーブル
    using EventListenerTable = std::list<EventListenerPtr>;
    
    //  リスナーのリストと特定のイベントの関連付け
    using EventListenerMap = std::map<uint32_t, EventListenerTable>;
    
    //  EventListenerMapの検索結果
    using EventListenerMapEntry = std::pair<uint32_t, EventListenerTable>;
    
    //  EventListenerMapへの挿入結果
    using EventListenerMapInsertResult = std::pair<EventListenerMap::iterator, bool>;
    
    //  イベントキュー
    using EventQueue = std::list<EventHandle>;

public:
    explicit EventManager(
        const char* const name,
        bool set_as_global
    );
    
    ~EventManager();
    
public:
    bool addListener(
        const EventListenerPtr& in_handler,
        const EventType& in_type
    ) override;
    
    
    bool removeListener(
        const EventListenerPtr& in_handler,
        const EventType& in_type
    ) override;
    
    bool removeListener(
        const EventListenerPtr& listener
    ) override;
    
    bool triggerEvent(
        const EventHandle& in_event
    ) override;
    
    bool queueEvent(
        const EventHandle& in_event
    ) override;
    
    bool abortEvent(
        const EventType& in_type,
        bool all_type = false
    ) override;
    
    bool tick(
        uint32_t proc_limit = 999999
    ) override;
    
    
    bool isValidateEventType(const EventType& in_type) const override;

    EventListenerList getListenerList(
        const EventType& event_type
    ) const;

    EventTypeList getTypeList() const;
    
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

