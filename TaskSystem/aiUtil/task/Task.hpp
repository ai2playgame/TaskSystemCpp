#pragma once

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
    std::unique_ptr<TaskCondition> eraseCond_;

    template<class EraseConditionTy,
             std::enable_if_t<std::is_base_of_v<TaskCondition, EraseConditionTy>>* = nullptr>
    Task(EraseConditionTy&& cond)
        : eraseCond_{ std::make_unique<EraseConditionTy>(std::forward<EraseConditionTy>(cond)) }
    {}
    Task()
        : eraseCond_{ std::make_unique<TaskCondition>() }
    {}
private:
    friend class TaskSystem;

};

inline bool Task::updateCondition() const
{
    // cond_は削除フラグ
    return !eraseCond_->updateCondition();
}

inline void Task::destroy()
{
    eraseCond_ = std::make_unique<TaskCondition>(true);
}
}
