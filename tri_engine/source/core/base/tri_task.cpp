////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


//  include
#include "core/base/tri_task.hpp"


TRI_CORE_NS_BEGIN

TaskBase::TaskBase()
    : priority_(PRIORITY_APP_DEFAULT)
    , type_(0)
    , pause_lv_(PAUSE_LV_1)
    , kill_(false)
    , children_()
{}



TaskBase::~TaskBase() {

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
    if (kill_) {
        //  キル済タスクは何もしない
        //  親タスク側でインスタンスが破棄される
        return;
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



TRI_CORE_NS_END

