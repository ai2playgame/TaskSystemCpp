﻿#pragma once

#include <Siv3D.hpp>
#include "TaskCondition.hpp"

namespace aiUtil::task {
/*
TODO: タスク間通信
*/
class Task {
public:

    virtual ~Task() = default;
    virtual void update() = 0;

    /// <summary>
    /// 実行するかどうかの判定
    /// </summary>
    /// <returns></returns>
    virtual bool updateCondition() const;
    virtual void destroy() final;

protected:
    std::unique_ptr<TaskCondition> cond_;

    template<class EraseConditionTy,
             std::enable_if_t<std::is_base_of_v<TaskCondition, EraseConditionTy>>* = nullptr>
    Task(EraseConditionTy&& cond)
        : cond_{ std::make_unique<EraseConditionTy>(std::forward<EraseConditionTy>(cond)) }
    {}
    Task()
        : cond_{ std::make_unique<TaskCondition>() }
    {}
private:
    friend class TaskSystem;

};

inline bool Task::updateCondition() const
{
    return cond_->updateCondition();
}

inline void Task::destroy()
{
    cond_ = std::make_unique<TaskCondition>(true);
}
}
