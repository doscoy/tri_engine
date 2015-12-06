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
#include "core/kernel/memory/tri_new.hpp"

TRI_CORE_NS_BEGIN

///
/// タスク
class TaskGeneratorBase;
class TaskBase;
using TaskPtr = SharedPtr<TaskBase>;
using TaskList = List<TaskPtr>;

class TaskBase
    : private Uncopyable
    , virtual public Nameable
{
    friend class Director;
    using self_t = TaskBase;
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
    TaskBase();
    

public:
    ///
    /// デストラクタ
    virtual ~TaskBase();

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
    bool operator <(const TaskBase& rhs) {
        return priority_ < rhs.priority_;
    }
    
    ///
    /// operator >
    bool operator >(const TaskBase& rhs) {
        return priority_ > rhs.priority_;
    }
    
    ///
    /// 削除予定か
    bool isKill() const {
        return kill_;
    }
    
    ///
    /// 子タスク生成
    template <class U>
    auto createTask() {
        SharedPtr<U> t(T3_NEW U());
        addTask(t);
        return t;
    }
    
    ///
    /// タスクの追加
    void addTask(TaskPtr child);

    ///
    /// 親タスク
    auto parent() const {
        return parent_;
    }
    
    ///
    /// 親タスク
    void parent(TaskBase* p) {
        parent_ = p;
    }

    ///
    /// 子タスクがあるか判定
    bool hasChild() const {
        return !children_.empty();
    }
    
private:

    ///
    /// タスクの初期化呼び出し
    ///
    void doTaskInitialize();
    
    ///
    /// タスクの後片付け呼び出し
    ///
    void doTaskTerminate();
    
    ///
    /// タスクの更新呼び出し
    /// 子タスクの更新と
    void doTaskUpdate(
        const DeltaTime dt
    );
    
protected:
    ///
    /// タスクの初期化
    /// createTask直後に呼ばれる
    virtual void onTaskFirstUpdate() {}

    ///
    /// タスクの更新
    /// 毎フレーム呼ばれる
    virtual void onTaskUpdate(const DeltaTime dt) {}

    ///
    /// タスクの後片付け
    /// killTask呼び出し時に呼ばれる
    virtual void onTaskKill() {}

public:
    ///
    /// タスクの削除予約
    void killTask() {
        kill_ = true;
        doTaskTerminate();
        for (auto& child : children_) {
            child->killTask();
        }
    }
    

private:
    int priority_;          ///< 優先度
    int type_;              ///< タイプ
    PauseLevel pause_lv_;   ///< ポーズレベル

    //  最初のアップデートでinitializeを呼ぶ
    bool first_update_;

    //  タスク削除リクエスト
    bool kill_;

    /// 子タスク
    TaskList children_;
    
    /// 次タスク
    /// 自身のkillと共に生成されるタスク
    TaskGeneratorBase* next_;
    
    ///
    /// 親タスク
    TaskBase* parent_;
};


///
/// タスクジェネレータ基底
class TaskGeneratorBase {
public:
    virtual TaskPtr generate() = 0;
};

///
/// タスクジェネレータ
/// 次に生成するタスクの予約用
template <class T>
class TaskGenerator
    : public TaskGeneratorBase
{
public:
    static TaskGenerator* instancePtr() {
        static TaskGenerator<T> inst_;
        return &inst_;
    }

    TaskPtr generate() override {
        TaskPtr t(T3_NEW T);
        return t;
    }
};

///
/// タスクファクトリ
/// 一定時間毎に指定のタスクを生成する
class TaskFactory
    : public TaskBase {
public:

    TaskFactory()
        : TaskBase()
        , timer_(0)
        , interval_(0)
        , count_(0)
        , max_count_(0)
    {}

    void order(
        float start_delay,
        float interval,
        TaskGeneratorBase* generator,
        int max_count = std::numeric_limits<std::uint32_t>::max()
    ) {
        count_ = 0;
        generator_ = generator;
        timer_ = start_delay;
        interval_ = interval;
        max_count_ = max_count;
    }
    
    
    void onTaskUpdate(const DeltaTime dt) override {
        timer_ -= dt;
        if (timer_ < 0) {
            timer_ = interval_;
            //  生成したタスクはこのタスクの子ではなく、親タスクに繋げる
            //  このタスクは生成後すぐに削除されるため
            auto task = generator_->generate();
            parent()->addTask(task);
            count_ += 1;
            if (count_ >= max_count_) {
                killTask();
            }
        }
    }

private:
    float timer_;
    float interval_;
    TaskGeneratorBase* generator_;
    std::uint32_t count_;
    std::uint32_t max_count_;
};


///
/// タスクシステムルート
class RootTask
    : public TaskBase
{
    void onTaskUpdate(const DeltaTime dt) override {}
};


TRI_CORE_NS_END



#endif // TRI_TASK_HPP_INCLUDED

