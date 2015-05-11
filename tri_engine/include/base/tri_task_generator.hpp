/**
    @file tri_task_generator.hpp
    タスクジェネレータ.
*/

#ifndef TRI_TASK_GENERATOR_HPP_INCLUDED
#define TRI_TASK_GENERATOR_HPP_INCLUDED

//  include
#include "tri_task.hpp"
#include "tri_scene.hpp"

namespace t3 {


///
/// タスク生成タスク.
/// あるタスクを生成するためのタスク
template <typename T>
class TaskGenerator
    : public Task
{
public:
    ///
    /// コンストラクタ
    TaskGenerator()
        : Task()
        , timer_(0.0f)
        , interval_(0.0f)
        , interval_add_(0.0f)
    {}

public:
    ///
    /// 更新
    void taskUpdate(const t3::tick_t dt) {
        timer_ += dt;
        if (timer_ > interval_) {
            //  インターバルを消化したのでタスク生成
            timer_ = 0.0f;
            
            //  次回までのインターバル値の変化
            interval_ += interval_add_;
            
            //  タスク生成
            auto task = std::make_shared<T>();
            t3::SceneManager::addSceneTask(task);   // 登録
        }
    }

    ///
    /// タスクが生成されるインターバルを設定
    void interval(float interval) {
        interval_ = interval;
    }
    ///
    /// 回数を重ねるたびにインターバルの値を変化させるための加算値
    void intervalAdd(float add) {
        interval_add_ = add;
    }


public:
    float timer_;       ///< タイマー
    float interval_;    ///< インターバル
    float interval_add_;///< インターバル変化値
};


}

#endif // TRI_TASK_GENERATOR_HPP_INCLUDED
