////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_task.hpp
    タスク.
*/

#ifndef TRI_TASK_HPP_INCLUDED
#define TRI_TASK_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/base/tri_types.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "core/utility/tri_nameable.hpp"
#include "tri_pause_level.hpp"
#include "tri_event_manager.hpp"
#include "core/base/tri_std.hpp"
#include "core/kernel/memory/tri_new.hpp"

TRI_CORE_NS_BEGIN

///
/// タスク
class Task;
using TaskPtr = SharedPtr<Task>;
using TaskList = List<TaskPtr>;

class Task
    : private Uncopyable
    , virtual public Nameable
{
    friend class Director;
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

protected:
    ///
    /// コンストラクタ
    Task();
    
    ///
    /// コンストラクタ
    Task(
        int type,
        int priority,
        PauseLevel pause_lv
    );

public:
    ///
    /// デストラクタ
    virtual ~Task();

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
    /// ポーズレベル取得
    PauseLevel pauseLevel() const {
        return pause_lv_;
    }
    
    ///
    /// ポーズレベル設定
    void pauseLevel(const PauseLevel lv) {
        pause_lv_ = lv;
    }

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
    
    ///
    /// 削除予定か
    bool isKill() const {
        return kill_;
    }

    ///
    /// タスクの更新
    /// 子タスクの更新と
    void taskFrame(
        const DeltaTime dt
    );

    ///
    /// タスクの更新
    virtual void taskUpdate(
        const DeltaTime dt
    ) {}


    ///
    /// 子タスク生成
    template <class T>
    auto createTask() {
        SharedPtr<T> t(T3_NEW T());
        children_.push_back(t);
        return t;
    }
    
    
protected:
    void killTask() {
        kill_ = true;
    }
    

private:
    int priority_;          ///< 優先度
    int type_;              ///< タイプ
    PauseLevel pause_lv_;   ///< ポーズレベル

    //
    bool kill_;

    /// 子タスク
    TaskList children_;
};



TRI_CORE_NS_END



#endif // TRI_TASK_HPP_INCLUDED

