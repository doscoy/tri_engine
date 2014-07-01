
#include "base/tri_event_manager.hpp"
#include "dbg/tri_assert.hpp"
#include "math/tri_math_util.hpp"
#include "base/tri_task.hpp"
#include "base/tri_scene.hpp"

namespace t3 {
inline namespace base {


class LounchEventTask
    : public Task
{
public:
    LounchEventTask(const EventHandle& event)
        : Task()
        , event_(event)
    {
    }
    
    void taskUpdate(
        const tick_t delta_time
    ) override {
        safeQueueEvent(event_);
        killTask();
    }
    
private:
    EventHandle event_;
};




EventManagerBase* event_manager_ = nullptr;

EventManagerBase* EventManagerBase::get() {
    return event_manager_;
}

EventManagerBase::EventManagerBase(
    const char* const name,
    bool set_as_global
) {
    if (set_as_global) {
        event_manager_ = this;
    }
}

EventManagerBase::~EventManagerBase() {
    if (event_manager_ == this) {
        event_manager_ = nullptr;
    }
}












bool safeAddListener(
    const EventListenerPtr& in_handler,
    const EventType& in_type
) {
    T3_ASSERT(EventManagerBase::get());
    return EventManagerBase::get()->addListener(in_handler, in_type);
}

bool safeRemoveListener(
    const EventListenerPtr& in_handler,
    const EventType& in_type
) {
    T3_ASSERT(EventManagerBase::get());
    return EventManagerBase::get()->removeListener(in_handler, in_type);

}

bool safeRemoveListener(
    const EventListenerPtr& listener
) {
    T3_ASSERT(EventManagerBase::get());
    return EventManagerBase::get()->removeListener(listener);
}

bool safeTriggerEvent(
    const EventHandle& in_event
) {
    T3_ASSERT(EventManagerBase::get());
    return EventManagerBase::get()->triggerEvent(in_event);

}

bool safeQueueEvent(
    const EventHandle& in_event
) {
    T3_ASSERT(EventManagerBase::get());
    return EventManagerBase::get()->queueEvent(in_event);

}

void safeQueueEvent(
    const EventHandle& in_event,
    float delay_sec
) {
    auto lounch_event = std::make_shared<LounchEventTask>(in_event);
    auto delay_task = std::make_shared<WaitingTask>(delay_sec);
    delay_task->setNextTask(lounch_event);
    t3::SceneManager::addSceneTask(delay_task);
}


bool safeAbortEvent(
    const EventType& in_type,
    bool all_type
) {
    T3_ASSERT(EventManagerBase::get());
    return EventManagerBase::get()->abortEvent(in_type, all_type);

}

bool safeTickEventManager(
    uint32_t max_milli
) {
    T3_ASSERT(EventManagerBase::get());
    return EventManagerBase::get()->tick(max_milli);
}

bool safeValidateEventType(
    const EventType& in_type
) {
    T3_ASSERT(EventManagerBase::get());
    return EventManagerBase::get()->isValidateEventType(in_type);
}










EventManager::EventManager(
    const char* const name,
    bool set_as_global
)   : EventManagerBase(name, set_as_global)
    , active_queue_(0)
{
    
}


EventManager::~EventManager() {
    active_queue_ = 0;
}


bool EventManager::addListener(
    const EventListenerPtr& in_listener,
    const EventType& in_type
) {

    if (!isValidateEventType(in_type)) {
        return false;
    }

    
    //  リスナーマップのエントリを探しこのエントリに対応するテーブルが
    //  まだ存在しなければエントリを作成
    EventListenerMap::iterator elm_it = registry_.find(in_type.key());
    
    if (elm_it == registry_.end()) {
        //  未発見なのでエントリを作成
        EventListenerMapInsertResult elm_res = registry_.insert(
            EventListenerMapEntry(in_type.key(), EventListenerTable())
        );
        
        if (elm_res.second == false) {
            //挿入失敗
            return false;
        }
        
        if (elm_res.first == registry_.end()) {
            //  空のテーブル
            return false;
        }
        
        //  これでマップリストを更新できるようになる
        elm_it = elm_res.first;
    }
    
    //  リスナーのマップリストを更新する
    //  既存のリストをたどりリスナーを二重に追加することを防ぐ
    EventListenerTable& table = (*elm_it).second;
    
    EventListenerTable::iterator end = table.end();
    for (EventListenerTable::iterator it = table.begin();
        it != end; ++it) {
        if (*it == in_listener) {
            //  追加済だった
            return false;
        }
    }
    
    
    //  イベント型の有効性確認
    //  リスナーの有効性確認
    table.push_back(in_listener);
    
    
    
    return true;
}



bool EventManager::removeListener(
    const EventListenerPtr& in_listener,
    const EventType& in_type
) {
    if (!isValidateEventType(in_type)) {
        return false;
    }
    
    return removeListener(in_listener);
}

bool EventManager::removeListener(const EventListenerPtr &listener) {
    bool result = false;
    
    //  総当り
    EventListenerMap::iterator map_it = registry_.begin();
    EventListenerMap::iterator map_end = registry_.end();
    for (; map_it != map_end; ++map_it) {
        
        EventListenerTable& table = map_it->second;
        
        EventListenerTable::iterator table_it = table.begin();
        EventListenerTable::iterator table_end = table.end();
        
        for (; table_it != table_end; ++table_it) {
            if (*table_it == listener) {
                table.erase(table_it);
                
               
                result = true;
                
                //  addListenerにおいてイベントの処理リストにリスナーが
                //  重複しないことを保証しているので内側のループは抜けて良い
                break;
            }
        }
        
        
    }
    return result;

}


bool EventManager::triggerEvent(
    const t3::EventHandle& in_event
) {
    if (!isValidateEventType(in_event->getEventType())) {
        return false;
    }

    EventListenerMap::const_iterator it_wc = registry_.find(0);
    
    if (it_wc != registry_.end()) {
        const EventListenerTable& table = it_wc->second;
        
        EventListenerTable::const_iterator table_it = table.begin();
        EventListenerTable::const_iterator table_end = table.end();
        for (; table_it != table_end; ++table_it) {
            (*table_it)->handleEvent(*in_event);
        }
    }
    
    EventListenerMap::const_iterator it = registry_.find((in_event->getEventType().key()));
    
    if (it == registry_.end()) {
        return false;
    }
    
    const EventListenerTable& table = it->second;


    bool processed = false;

    EventListenerTable::const_iterator table_it = table.begin();
    EventListenerTable::const_iterator table_end = table.end();
    
    for (; table_it != table_end; ++table_it) {
        EventListenerPtr listener = *table_it;
        listener->handleEvent(*in_event);
    }

    return processed;
}



bool EventManager::queueEvent(
    const EventHandle& in_event
) {

    T3_ASSERT(inRange(active_queue_, (int)0, (int)NUM_QUEUES));
    
    if (!isValidateEventType(in_event->getEventType())) {
        return false;
    }
    
    EventListenerMap::const_iterator map_it = registry_.find(in_event->getEventType().key());
    
    if (map_it == registry_.end()) {
        //  グローバルリスナーがアクティブでなければキューへの追加は中止
        EventListenerMap::const_iterator it_wc = registry_.find(0);
        
        if (it_wc == registry_.end()) {
            //  このイベントのリスナはいないのでスキップ
            T3_TRACE("%s is skip\n", in_event->getEventType().string().c_str());
            dumpListeners();
            return false;
        }
    }

    queues_[active_queue_].push_back(in_event);
    return true;
}




bool EventManager::abortEvent(
    const EventType& in_type,
    bool all_of_type
) {
    T3_ASSERT(inRange(active_queue_, (int)0, (int)NUM_QUEUES));

    if (isValidateEventType(in_type)) {
        return false;
    }
    
    EventListenerMap::iterator it = registry_.find(in_type.key());
    
    if (it == registry_.end()) {
        return false; // このリスナーはいないのでスキップ
    }

    bool result = false;
    
    EventQueue& queue = queues_[active_queue_];
    
    EventQueue::iterator queue_it = queue.begin();
    EventQueue::iterator queue_end = queue.end();
    
    for (; queue_it != queue_end; ++queue_it) {
        if ((*queue_it)->getEventType() == in_type) {
            queue_it = queue.erase(queue_it);
            result = true;
            if (!all_of_type) {
                break;
            }
            else {
                ++queue_it;
            }
        }
    }

    return result;
}



bool EventManager::tick(
    uint32_t proc_limit
) {

    EventListenerMap::const_iterator it_wc = registry_.find(0);
    
    //  アクティブなキューを交換
    int queue_to_process = active_queue_;
    active_queue_ = (active_queue_ + 1) % NUM_QUEUES;
    queues_[active_queue_].clear();
    
    EventQueue& active_queue = queues_[active_queue_];
    EventQueue& process_queue = queues_[queue_to_process];
    
    //  リミットまでイベントを処理
    int process_count = 0;
    while (process_queue.size() > 0) {
        EventHandle event = process_queue.front();
        process_queue.pop_front();
        
        const EventType& event_type = event->getEventType();
        
        EventListenerMap::const_iterator map_it =registry_.find(event_type.key());
        
        if (it_wc != registry_.end()) {
            
            const EventListenerTable& table = it_wc->second;
            
            EventListenerTable::const_iterator table_it = table.begin();
            EventListenerTable::const_iterator table_end = table.end();
            
            for (; table_it != table_end; ++table_it) {
                (*table_it)->handleEvent(*event);
            }
        }
        
        // このイベント型にはリスナーが居ないのでスキップ
        if (map_it == registry_.end()) {
            continue;
        }
        
        const EventListenerTable& table = map_it->second;
        EventListenerTable::const_iterator table_it = table.begin();
        EventListenerTable::const_iterator table_end = table.end();
        
        for (; table_it != table_end; ++table_it) {
            (*table_it)->handleEvent(*event);
        }
        
        process_count += 1;
        
        if (process_count >= proc_limit) {
            break;
        }
    }

    //  処理すべきイベントが残ってる場合アクティブなキューにプッシュしておく
    //  並び方を維持するために残りの順序を逆にしてアクティブなキューの先頭に挿入
    bool queue_flushed = (process_queue.size() == 0);
    
    if (!queue_flushed) {
        while (process_queue.size() > 0) {
            EventHandle event = process_queue.back();
            process_queue.pop_back();
            active_queue.push_front(event);
        }
    }
    
    return queue_flushed;
}


bool EventManager::isValidateEventType(
    const EventType& in_type
) const {

    if (in_type.string().length() == 0) {
        return false;
    }
    
    if (in_type.key() == 0) {
        return false;
    }
    
    
    T3_ASSERT_MSG(
        type_list_.find(in_type) == type_list_.end(),
        "it was provavly not registerd whit the EventManager."
    );

    return true;
}

EventListenerList EventManager::getListenerList(
    const EventType &event_type
) const {
    if (!isValidateEventType(event_type)) {
        return EventListenerList();
    }
    
    EventListenerMap::const_iterator map_it = registry_.find(event_type.key());
    if (map_it == registry_.end()) {
        //  このイベント型にはリスナーがいない
        return EventListenerList();
    }
    
    
    const EventListenerTable& table = map_it->second;
    if (table.empty()) {
        //  このイベント型には以前はリスナーがあったが現在は無い
        return EventListenerList();
    }
    
    EventListenerList result;
    result.reserve(table.size());
    
    
    EventListenerTable::const_iterator table_it = table.begin();
    EventListenerTable::const_iterator table_end = table.end();
    for (; table_it != table_end; ++table_it) {
        result.push_back(*table_it);
    }
    
    return result;
}

EventTypeList EventManager::getTypeList() const {
    if (type_list_.empty()) {
        return EventTypeList();
    }
    
    EventTypeList result;
    result.reserve(type_list_.size());
    
    EventTypeSet::const_iterator it = type_list_.begin();
    EventTypeSet::const_iterator end = type_list_.end();
    
    for (; it != end; ++it) {
        result.push_back(*it);
    }
    
    return result;
}


void EventManager::dumpListeners() const {
    
    //  登録済の全名前出力
    EventListenerMap::const_iterator map_it = registry_.begin();
    EventListenerMap::const_iterator map_end = registry_.end();
    for (; map_it != map_end; ++map_it) {
        
        const EventListenerTable& table = map_it->second;
        
        EventListenerTable::const_iterator table_it = table.begin();
        EventListenerTable::const_iterator table_end = table.end();
        
        for (; table_it != table_end; ++table_it) {
            const EventListenerPtr listener = *table_it;
            T3_TRACE("%s -- %s\n",
                listener->getName().c_str(),
                getEventNameByKey(map_it->first).c_str()
            );
        }
        
    }
}


std::string EventManager::getEventNameByKey(
    HashString::key_t key
) const {

    for (auto type:type_list_) {
    
        if (type.key() == key) {
            return type.string();
        }
    }
    
    return "not found.";
}




}   // namespace base
}   // namespace t3