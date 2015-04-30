//
//  tri_task_generator.hpp
//  tri_engine
//
//  Created by KANI Tetsuro on 2014/11/23.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#ifndef tri_engine_tri_task_generator_hpp
#define tri_engine_tri_task_generator_hpp


#include "tri_task.hpp"
#include "tri_scene.hpp"

namespace t3 {



//  タスクジェネレータ
template <typename T>
class TaskGenerator
    : public Task
{
public:
    TaskGenerator()
        : Task()
        , timer_(0.0f)
        , interval_(0.0f)
        , interval_add_(0.0f)
    {
    }

public:
    void taskUpdate(const t3::tick_t dt) {
        timer_ += dt;
        if (timer_ > interval_) {
            timer_ = 0.0f;
            interval_ += interval_add_;
            auto task = std::make_shared<T>();
            t3::SceneManager::addSceneTask(task);
        }
    }

    void interval(float interval) {
        interval_ = interval;
    }
    
    void intervalAdd(float add) {
        interval_add_ = add;
    }


public:
    float timer_;
    float interval_;
    float interval_add_;
};


}


#endif
