////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


//  include
#include "core/base/tri_task.hpp"
#include "core/base/tri_task_manager.hpp"
#include "core/base/tri_director.hpp"


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
{
    Director::attachTask(this);
}



Task::~Task() {
    Director::detachTask(this);
}



TRI_CORE_NS_END

