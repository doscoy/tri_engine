////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/base/tri_event_manager.hpp"
#include "core/debug/tri_assert.hpp"
#include "core/math/tri_math_util.hpp"
#include "core/base/tri_task.hpp"
#include "core/base/tri_scene.hpp"

TRI_CORE_NS_BEGIN


EventManager::EventTypeSet EventManager::type_list_;
EventManager::EventListenerMap EventManager::registry_;
EventManager::EventQueue EventManager::queue_;


bool EventManager::addListenerCore(
    const EventHandler& in_listener,
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
    
    
    //  イベント型の有効性確認
    //  リスナーの有効性確認
    table.push_back(in_listener);
    
    return true;
}



bool EventManager::removeListener(
    const EventListenerPtr in_listener,
    const EventType& in_type
) {
    if (!isValidateEventType(in_type)) {
        return false;
    }
    
    return removeListener(in_listener);
}

bool EventManager::removeListener(const EventListenerPtr listener) {
    bool result = false;
    
    //  総当り
    EventListenerMap::iterator map_it = registry_.begin();
    EventListenerMap::iterator map_end = registry_.end();
    for (; map_it != map_end; ++map_it) {
        
        EventListenerTable& table = map_it->second;
        
        EventListenerTable::iterator table_it = table.begin();
        EventListenerTable::iterator table_end = table.end();
        
        for (; table_it != table_end; ++table_it) {
            if ((*table_it)->target() == listener) {
                
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



bool EventManager::queueEvent(
    const EventPtr& in_event
) {    
    if (!isValidateEventType(in_event->eventType())) {
        return false;
    }
    
    EventListenerMap::const_iterator map_it = registry_.find(in_event->eventType().key());
    
    if (map_it == registry_.end()) {
        //  グローバルリスナーがアクティブでなければキューへの追加は中止
        EventListenerMap::const_iterator it_wc = registry_.find(0);
        
        if (it_wc == registry_.end()) {
            //  このイベントのリスナはいないのでスキップ
            return false;
        }
    }

    queue_.push_back(in_event);
    return true;
}




bool EventManager::abortEvent(
    const EventType& in_type,
    bool all_of_type
) {


    if (isValidateEventType(in_type)) {
        return false;
    }
    
    EventListenerMap::iterator it = registry_.find(in_type.key());
    
    if (it == registry_.end()) {
        return false; // このリスナーはいないのでスキップ
    }

    bool result = false;
    
    EventQueue& queue = queue_;
    
    EventQueue::iterator queue_it = queue.begin();
    EventQueue::iterator queue_end = queue.end();
    
    for (; queue_it != queue_end; ++queue_it) {
        if ((*queue_it)->eventType() == in_type) {
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



bool EventManager::broadCast() {

    EventListenerMap::iterator it_wc = registry_.find(0);
    
    EventQueue& process_queue = queue_;
    
    //  全イベントを処理
    while (process_queue.size() > 0) {
        EventPtr event = process_queue.front();
        process_queue.pop_front();
        
        const EventType& event_type = event->eventType();
        
        
        if (it_wc != registry_.end()) {
            
            EventListenerTable& table = it_wc->second;
            
            EventListenerTable::iterator table_it = table.begin();
            EventListenerTable::iterator table_end = table.end();
            
            for (; table_it != table_end; ++table_it) {
                (*table_it)->arg1(&event);
                (*table_it)->invoke();
            }
        }
        
        // このイベント型にはリスナーが居ないのでスキップ
        EventListenerMap::iterator map_it =registry_.find(event_type.key());
        if (map_it == registry_.end()) {
            continue;
        }
        
        EventListenerTable& table = map_it->second;
        EventListenerTable::iterator table_it = table.begin();
        EventListenerTable::iterator table_end = table.end();
        
        for (; table_it != table_end; ++table_it) {
            (*table_it)->arg1(&event);
            (*table_it)->invoke();
        }
    }
    //  次のフレームまで持ち越すことは考えない

    return true;
}


bool EventManager::isValidateEventType(
    const EventType& in_type
) {

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
) {
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
        result.push_back((*table_it)->target());
    }
    
    return result;
}

EventTypeList EventManager::getTypeList() {
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


void EventManager::dumpListeners() {
    
    //  登録済の全名前出力
    EventListenerMap::const_iterator map_it = registry_.begin();
    EventListenerMap::const_iterator map_end = registry_.end();
    int listener_count = 0;
    for (; map_it != map_end; ++map_it) {
        
        const EventListenerTable& table = map_it->second;
        
        EventListenerTable::const_iterator table_it = table.begin();
        EventListenerTable::const_iterator table_end = table.end();
        
        for (; table_it != table_end; ++table_it) {
            listener_count += 1;
        }
        
    }

}


String EventManager::getEventNameByKey(
    HashString::key_t key
) {

    for (auto type:type_list_) {
    
        if (type.key() == key) {
            return type.string();
        }
    }
    
    return "not found.";
}


TRI_CORE_NS_END
