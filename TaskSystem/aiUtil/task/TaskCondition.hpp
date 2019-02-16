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
		: cond_{ std::move(condFunc) }
		, last_{ false }
	{}
	~TaskCondition() = default;
	explicit operator bool() const noexcept { return !!*this; }
	bool operator!() const noexcept { return !last_; }
	bool updateCondition()
	{
		return last_ = cond_();
	}
	void setNewCond(const std::function<bool()>& func) { cond_ = func; }
	void setNewCond(std::function<bool()>&& func) { cond_ = std::move(func); }
};

template<class Clock>
TaskCondition timer(typename Clock::time_point time)
{
	return TaskCondition([time = std::move(time)]() {return Clock::now() >= time; });
}
template<class Clock>
TaskCondition timer(const typename Clock::duration& duration)
{
	return TaskCondition([time = Clock::now() + duration]() {return Clock::now() >= time; });
}

}
