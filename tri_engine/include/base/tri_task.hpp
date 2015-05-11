/**
    @file tri_task.hpp
    タスク.
*/

#ifndef TRI_TASK_HPP_INCLUDED
#define TRI_TASK_HPP_INCLUDED

//  include
#include "base/tri_types.hpp"
#include "util/tri_uncopyable.hpp"
#include "util/tri_nameable.hpp"
#include "tri_pause_level.hpp"
#include "tri_event_manager.hpp"
#include "base/tri_std.hpp"


namespace t3 {

//  前方宣言
class TaskManager;

///
/// タスク
class Task
    : private Uncopyable
    , virtual public Nameable
{
    friend class TaskManager;
    using self_t = Task;
public:
    ///
    /// タスクのプライオリティ
    enum Priority {
        PRIORITY_SYS_AFTER_APP  =    100,   ///< 最後に実行されるタスク（システム用）
        PRIORITY_APP_LOW        =  10000,   ///< アプリ側で優先度の低いタスク
        PRIORITY_APP_DEFAULT    =  20000,   ///< アプリ側で通常優先度のタスク
        PRIORITY_APP_HIGH       =  30000,   ///< アプリ側で優先度の高いタスク
        PRIORITY_SYS_BEFORE_APP = 100000,   ///< 最初に実行されるタスク（システム用）
    };

public:
    ///
    /// コンストラクタ
    Task(int type)
        : Task(type, PRIORITY_APP_DEFAULT, PAUSE_LV_1)
    {}
    
    ///
    /// コンストラクタ
    Task()
        : Task(0, PRIORITY_APP_DEFAULT, PAUSE_LV_1)
    {}
    
    ///
    /// コンストラクタ
    Task(
        int type,
        int priority,
        PauseLevel pause_lv
    )   : priority_(priority)
        , type_(type)
        , kill_(false)
        , active_(true)
        , inital_update_(true)
        , attached_(false)
        , pause_lv_(pause_lv)
    {
    }
        
    ///
    /// デストラクタ
    virtual ~Task()
    {}

public:

    ///
    /// タスクのプライオリティ取得
    int taskPriority() const {
        return priority_;
    }
    
    ///
    /// タスクプライオリティ設定
    void taskPriority(const int priority){
        priority_ = priority;
    }
    
    ///
    /// タスクタイプ取得
    int type() const {
        return type_;
    }
    
    ///
    /// タスクタイプ設定
    void type(const int type) {
        type_ = type;
    }

    ///
    /// タスクが終了したか判定
    bool isTaskDead() const {
        return kill_;
    }
    
    ///
    /// 有効化されたタスクか判定
    bool activated() const {
        return active_;
    }
    
    ///
    /// タスクを有効化
    void activate(const bool active) {
        active_ = active;
    }
    
    ///
    /// タスクがアタッチ済か判定
    bool attachedTask() const {
        return attached_;
    }
    
    ///
    /// タスクをアタッチ
    void attachTask(const bool attached) {
        attached_ = attached;
    }
    
    ///
    /// 初期化済タスクか判定
    bool isTaskInitialized() const {
        return !inital_update_;
    }
    
    ///
    /// 次のタスク取得
    const SharedPtr<Task> nextTask() const {
        return next_;
    }
    
    ///
    /// 次のタスク設定
    const SharedPtr<Task> nextTask(SharedPtr<Task> next) {
        next_ = next;
        return next_;
    }
    
    ///
    /// タスクを破棄
    void killTask() {
        kill_ = true;
    };
    
    ///
    /// ポーズレベル取得
    PauseLevel pauseLevel() const {
        return pause_lv_;
    }
    
    ///
    /// ポーズレベル設定
    void pauseLevel(const PauseLevel lv) {
        pause_lv_ = lv;
    }

public:
    ///
    /// operator <
    bool operator <(const Task& rhs) {
        return priority_ < rhs.priority_;
    }
    
    ///
    /// operator >
    bool operator >(const Task& rhs) {
        return priority_ > rhs.priority_;
    }

public:
    ///
    /// タスクの更新
    virtual void taskFrame(tick_t delta_time) {
        taskUpdate(delta_time);
    }

    ///
    /// タスクの初期化
    virtual void taskInitialize() {}
    
    ///
    /// タスクの更新
    virtual void taskUpdate(const tick_t delta_time) {}
    
    ///
    /// タスクの後片付け
    virtual void taskTerminate() {}
    

private:
    int priority_;          ///< 優先度
    int type_;              ///< タイプ
    bool kill_;             ///< キルリクエストフラグ
    bool active_;           ///< 有効フラグ
    bool inital_update_;    ///<
    bool attached_;
    PauseLevel pause_lv_;   ///< ポーズレベル
    SharedPtr<Task> next_;  ///< 親タスク
    
};







class WaitingTask
    : public Task
{
public:
    WaitingTask(const tick_t wait_time)
        : Task()
        , now_(0)
        , end_time_(wait_time)
    {}
    
public:
    void taskUpdate(
        const tick_t delta_time
    ) override {
        if (activated()){
            now_ += delta_time;
            if (now_ >= end_time_) {
                killTask();
            }
        }
    }


private:
    float now_;
    float end_time_;

};

using TaskPtr = SharedPtr<Task>;



}   // namespace t3



#endif // TRI_TASK_HPP_INCLUDED






