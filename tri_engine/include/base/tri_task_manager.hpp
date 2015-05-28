/**
    @file tri_task_manager.hpp
    タスクマネージャ.
*/

#ifndef TRI_TASK_MANAGER_HPP_INCLUDED
#define TRI_TASK_MANAGER_HPP_INCLUDED

//  include
#include "tri_task.hpp"
#include "base/tri_std.hpp"


namespace t3 {

///
/// タスクコンテナ
typedef List<TaskPtr> TaskList;

///
/// タスクマネージャ
class TaskManager
    : Uncopyable {
public:
    ///
    /// コンストラクタ
    TaskManager();
    
    ///
    /// デストラクタ
    ~TaskManager();
    
public:
    ///
    /// タスクアタッチ
    void attach(TaskPtr task);
    
    ///
    /// タスクを持っているか
    bool hasTask() {
        return !taskes_.empty();
    }
        
    ///
    /// タスク更新
    void updateTask(const tick_t delta_time);
    
    
    ///
    /// 全タスクを表示
    void printTask() const;
    
    ///
    /// タスク数を取得
    std::size_t count() const {
        return taskes_.size();
    }
    
    ///
    /// タスク数を取得.
    /// 条件指定バージョン
    std::size_t count(
        std::function<bool(const TaskPtr)> func ///< この条件に合致するタスクを数える
    ) const {
        return std::count_if(taskes_.begin(), taskes_.end(), func);
    }
    
    
protected:
    ///
    /// 管理タスク
    TaskList taskes_;
    
private:
    ///
    /// タスクを外す
    void detach(TaskPtr task) {
        taskes_.remove(task);
        task->attachTask(false);
    }
    
    ///
    /// 管理している全てのタスクを破棄
    void killAllTask();
    
    ///
    /// ポーズコールバック
    void onPause(const EventPtr);
    
    ///
    /// レジュームコールバック
    void onResume(const EventPtr);
    
private:
    PauseLevel pause_level_;    ///< ポーズレベル
};

}   // namespace t3

#endif // TRI_PROCESS_MANAGER_HPP_INCLUDED