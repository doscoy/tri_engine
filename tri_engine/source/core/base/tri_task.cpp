////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


//  include
#include "core/base/tri_task.hpp"
#include "core/base/tri_director.hpp"

TRI_CORE_NS_BEGIN

TaskBase::TaskBase()
    : priority_(PRIORITY_APP_DEFAULT)
    , type_(0)
    , pause_lv_(PAUSE_LV_1)
    , first_update_(true)
    , kill_(false)
    , children_()
    , next_(nullptr)
    , parent_(nullptr)
{
    
}



TaskBase::~TaskBase() {
    //  次のタスクがある場合は破棄タイミングで生成
    if (next_) {
        T3_NULL_ASSERT(parent_);
        parent_->addTask(next_->generate());
    }
}

void TaskBase::doTaskInitialize() {
    taskInitialize();
}

void TaskBase::doTaskTerminate() {
    taskTerminate();
}

void TaskBase::doTaskUpdate(
    const DeltaTime dt
) {
    //  前フレームでキル済のを取り除く
    children_.remove_if(
        [](TaskPtr p){
            return p->isKill();
        }
    );
    
    if (kill_) {
        //  キル済タスクは何もしない
        //  親タスク側でインスタンスが破棄される
        return;
    }

    if (first_update_) {
        first_update_ = false;
        doTaskInitialize();
    }

    taskUpdate(dt);

    //  直前のアップデートでkillされてなければ子タスクを実行
    if (!kill_) {
        for (auto& child : children_) {
            child->doTaskUpdate(dt);
        }
    }
    
    children_.remove_if(
        [](TaskPtr p){
            return p->isKill();
        }
    );
}


void TaskBase::addTask(
    TaskPtr child
) {
    T3_NULL_ASSERT(child.get());
    children_.push_back(child);
    child->parent_ = this;
}



TRI_CORE_NS_END

