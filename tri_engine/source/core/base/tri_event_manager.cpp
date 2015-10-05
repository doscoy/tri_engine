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

///
/// 静的メンバ
EventManager::EventTypeSet EventManager::type_list_;
EventManager::EventListenerMap EventManager::registry_;
EventManager::EventQueue EventManager::queue_[2];
int EventManager::current_queue_id_;
int EventManager::back_queue_id_;

///
/// イベントマネージャ初期化
void EventManager::initialize() {
    current_queue_id_ = 0;
    back_queue_id_ = 1;
}



///
/// カレントのキューを切り替える
void EventManager::switchQueue() {
    if (current_queue_id_ == 0) {
        current_queue_id_ = 1;
        back_queue_id_ = 0;
    } else {
        current_queue_id_ = 0;
        back_queue_id_ = 1;
    }
}

///
/// カレントキューを取得
EventManager::EventQueue& EventManager::currentQueue() {
    return queue_[current_queue_id_];
}

///
/// バックキューを取得
EventManager::EventQueue& EventManager::backQueue() {
    return queue_[back_queue_id_];
}


///
/// リスナー追加
bool EventManager::addListenerCore(
    const EventHandler& in_listener,
    const EventType& in_type
) {

    if (!isValidateEventType(in_type)) {
        //  無効なイベント
        return false;
    }

    
    //  リスナーマップのエントリを探し、このエントリに対応するテーブルが
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
    
    for (auto& it : table) {
        //  既に同じインスタンスのハンドラが登録されている
        T3_ASSERT(it->target() != in_listener->target());
    }
    
    
    //  まだ未登録だったので登録する
    table.push_back(in_listener);
    
    return true;
}


///
/// 全イベントへのリスナー登録削除
bool EventManager::removeListener(
    const EventListenerPtr listener
) {
    bool result = false;
    
    //  総当り
    auto map_it = registry_.begin();
    auto map_end = registry_.end();
    for (; map_it != map_end; ++map_it) {
        
        EventListenerTable& table = map_it->second;
        
        auto table_it = table.begin();
        auto table_end = table.end();
        
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


///
/// イベント登録
bool EventManager::queueEvent(
    const EventPtr& in_event
) {    
    if (!isValidateEventType(in_event->eventType())) {
        //  無効なイベント登録はスキップ
        return false;
    }

    //  リスナーが存在しないイベントの登録はスキップ
    auto listener_map = registry_.find(in_event->eventType().key());
    if (listener_map == registry_.end()) {
        //  未登録イベント = このイベントのリスナはいない
        //  スキップ
        return false;
    }

    //  イベントキューへ登録
    currentQueue().push_back(in_event);
    return true;
}





///
/// 毎フレーム呼ばれるイベント通達処理
bool EventManager::broadCast(
    const tick_t dt
) {
    //  キューを取得
    auto& current_queue = currentQueue();
    auto& back_queue = backQueue();
    
    //  全イベントを処理
    while (current_queue.size() > 0) {
        //  イベントをキューから取り出す
        auto event = current_queue.front();
        current_queue.pop_front();
        
        //  ブロードキャスト時間になっている？
        if (!event->isReady()) {
            //  まだ時間になっていない
            event->update(dt);
            //  バックキューに登録しなおし
            backQueue().push_back(event);
            
            //  このイベントの処理はここで終了。次へ。
            continue;
        }
        
        
        //  イベント発行
        
        
        const EventType& event_type = event->eventType();
        
        EventListenerMap::iterator map_it =registry_.find(event_type.key());
        if (map_it == registry_.end()) {
            //  このイベント型にはリスナーが居ない
            //  処理の必要がないのでスキップ
            continue;
        }
        
        //  リスナーリスト
        EventListenerTable& table = map_it->second;
        
        //  全リスナーにイベントを通知
        auto table_it = table.begin();
        auto table_end = table.end();
        for (; table_it != table_end; ++table_it) {
            //  引数を設定
            (*table_it)->arg1(&event);
            
            //  イベントハンドラ呼び出し
            (*table_it)->invoke();
        }
    }

    //  カレントキューを入れ替え
    switchQueue();

    return true;
}


///
/// イベントの有効性を判定
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

///
/// リスナーのリストを取得
EventListenerList EventManager::getListenerList(
    const EventType &event_type
) {
    if (!isValidateEventType(event_type)) {
        //  無効なイベントの場合
        //  空のリスナーリストを返す
        return EventListenerList();
    }
    
    //  イベントのリスナーリストを取得
    auto map_it = registry_.find(event_type.key());
    if (map_it == registry_.end()) {
        //  このイベント型にはリスナーがいない
        //  空のリストを返す
        return EventListenerList();
    }
    
    
    const EventListenerTable& table = map_it->second;
    if (table.empty()) {
        //  このイベント型には以前はリスナーがあったが現在は無い
        //  空のリストを返す
        return EventListenerList();
    }


    //  ※ここまで来るということは、このイベントの
    //  リスナーのリストは確かに存在する
    
    //  リスナーのリストを別インスタンスとして作成して返す
    
    EventListenerList result;
    result.reserve(table.size());
    
    
    auto table_it = table.begin();
    auto table_end = table.end();
    for (; table_it != table_end; ++table_it) {
        //  もどす用のリストにリスナーのリスト内容をコピー
        result.push_back((*table_it)->target());
    }
    
    //  もどす
    return result;
}

///
///  イベントタイプの一覧を取得
EventTypeList EventManager::getTypeList() {
    
    if (type_list_.empty()) {
        //  タイプリストが空
        return EventTypeList();
    }
    
    //  イベントタイプのリストを別インスタンスとして作成して返す
    EventTypeList result;
    result.reserve(type_list_.size());
    
    auto it = type_list_.begin();
    auto end = type_list_.end();
    
    for (; it != end; ++it) {
        //  もどす用のリストにリスナーのリスト内容をコピー
        result.push_back(*it);
    }
    
    return result;
}


///
/// リスナーの一覧をダンプ
void EventManager::dumpListeners() {
    
    //  登録済の全名前出力
    auto map_it = registry_.begin();
    auto map_end = registry_.end();
    int listener_count = 0;
    for (; map_it != map_end; ++map_it) {
        
        const auto& table = map_it->second;
        
        auto table_it = table.begin();
        auto table_end = table.end();
        
        for (; table_it != table_end; ++table_it) {
            listener_count += 1;
        }
        
    }

}

///
/// イベント名をハッシュキーから取得
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
