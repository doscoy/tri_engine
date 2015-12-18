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
#include "tri_pausable.hpp"
#include "tri_event_manager.hpp"
#include "core/kernel/memory/tri_new.hpp"

TRI_CORE_NS_BEGIN


//  タスクポインタ型定義
class TaskBase;
using TaskPtr = SharedPtr<TaskBase>;
using TaskList = List<TaskPtr>;



///
/// タスクジェネレータ基底
class TaskGeneratorBase {
public:
    virtual TaskPtr generate() = 0;
};



///
/// タスクジェネレータ
/// 任意の型のタスクを生成する
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
        SharedPtr<T> t(T3_NEW T);
        return t;
    }
};



///
/// タスク
class TaskBase
    : private Uncopyable
    , public Pausable
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
    template <class TaskType>
    SharedPtr<TaskType> createTask() {
        //  任意のタスク型のジェネレータ取得
        TaskGenerator<TaskType>* task_gen = TaskGenerator<TaskType>::instancePtr();
        
        //  ジェネレータからタスク生成
        SharedPtr<TaskType> t = std::dynamic_pointer_cast<TaskType>(createTask(task_gen));
        return t;
    }

    ///
    /// 子タスク生成
    /// ジェネレータで指定
    TaskPtr createTask(TaskGeneratorBase* gen) {
        TaskPtr t = gen->generate();
        addTask(t);
        return t;
    }

    ///
    /// 子タスクの追加リクエスト
    void addTaskRequest(TaskGeneratorBase* request) {
        add_requests_.push_back(request);
    }

    ///
    /// このタスクの破棄時に生成されるタスクを登録
    void nextTaskGenerator(
        TaskGeneratorBase* next
    ) {
        next_ = next;
    }

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
    /// タスクの追加
    void addTask(TaskPtr child);


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

protected:
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
    
    
    ///
    /// タスク追加リクエスト
    Vector<TaskGeneratorBase*> add_requests_;
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
            //  指定の時間が過ぎたら親タスクにタスク追加の依頼を出す
            parent()->addTaskRequest(generator_);
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



TRI_CORE_NS_END



#endif // TRI_TASK_HPP_INCLUDED

