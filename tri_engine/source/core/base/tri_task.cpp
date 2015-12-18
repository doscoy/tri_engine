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
    , first_update_(true)
    , kill_(false)
    , children_()
    , next_(nullptr)
    , parent_(nullptr)
{
    
}



TaskBase::~TaskBase() {
    //  次のタスクがある場合は破棄タイミングで親タスクにリクエストを送る
    if (next_) {
        T3_NULL_ASSERT(parent_);
        parent_->addTaskRequest(next_);
    }
}

void TaskBase::doTaskInitialize() {
    onTaskFirstUpdate();
}

void TaskBase::doTaskTerminate() {
    onTaskKill();
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

    if (!paused()) {
        onTaskUpdate(dt);
        
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
    
    //  タスク追加リクエストに応じる
    if (!add_requests_.empty()) {
        for (auto req : add_requests_) {
            createTask(req);
        }
    
        add_requests_.clear();
    }
}


void TaskBase::addTask(
    TaskPtr child
) {
    if (kill_) {
        return;
    }
    
    T3_NULL_ASSERT(child.get());
    children_.push_back(child);
    child->parent(this);
}



TRI_CORE_NS_END

