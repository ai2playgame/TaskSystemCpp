#pragma once
#include <utility>
#include <functional>
#include <chrono>

namespace aiUtil::task {

class TaskCondition {
    friend class Task;
    
    std::function<bool()> cond_;
    bool last_;
public:
    TaskCondition(bool initial = false)
        : cond_{ [initial]() {return initial; } }
        , last_{ initial }
    {}
    TaskCondition(std::function<bool()> condFunc)
        : cond_{std::move(condFunc)}
        , last_{ false }
    {}
    virtual ~TaskCondition() = default;
    explicit operator bool() const noexcept { return !!*this; }
    bool operator!() const noexcept { return !last_; }
    bool updateCondition() {
        return last_ = cond_();
    }
    void setNewCond(const std::function<bool()>& func) { cond_ = func; }
    void setNewCond(std::function<bool()>&& func) { cond_ = std::move(func); }
};

template<class Clock>
class Timer : TaskCondition {
public:
    Timer() = default;
    template<class Duration>
    Timer(const std::chrono::time_point<Clock, Duration>& timepoint)
        : cond_{ [timepoint]() { return Clock::now() >= timepoint; } }
    {}
    template<class Rep, class Ratio>
    Timer(const std::chrono::duration<Rep, Ratio>& duration)
        : cond_{ [timepoint = duration + Clock::now()](){ return Clock::now() >= timepoint; } }
    {}
};

}
