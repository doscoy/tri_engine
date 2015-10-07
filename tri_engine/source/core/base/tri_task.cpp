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

Task::Task()
    : Task(0, PRIORITY_APP_DEFAULT, PAUSE_LV_1)
{}


Task::Task(
    int type,
    int priority,
    PauseLevel pause_lv
)   : priority_(priority)
    , type_(type)
    , pause_lv_(pause_lv)
    , kill_(false)
    , children_()
{

}



Task::~Task() {

}

void Task::taskFrame(
    const DeltaTime dt
) {
    taskUpdate(dt);

    //  直前のアップデートでkillされてなければ子タスクを実行
    if (!kill_) {
        for (auto& child : children_) {
            child->taskFrame(dt);
        }
    }
    
    children_.remove_if(
        [](TaskPtr p){
            return p->isKill();
        }
    );
}



TRI_CORE_NS_END

