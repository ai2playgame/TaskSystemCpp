#pragma once
#include <utility>
#include <functional>
#include <type_traits>

namespace aiUtil::task {

class TaskFunction {
	std::function<void()> f_;
public:
	template<class T, std::enable_if_t<std::is_class_v<T>>* = nullptr>
	TaskFunction(T* ptr, void(T::*func)())
		: f_{ [ptr, func]() { (ptr->*func)(); } }
	{}
	TaskFunction(std::function<void()> func)
		: f_{std::move(func)}
	{}

	void operator()()
	{
		f_();
	}
	template<class T, std::enable_if_t<std::is_class_v<T>>* = nullptr>
	void setNewFunction(T* ptr, void(T::*func)())
	{
		f_ = [ptr, func] {ptr->*(*func)(); };
	}
	void setNewFunction(const std::function<void()>& func)
	{
		f_ = func;
	}
	void setNewFunction(std::function<void()>&& func)
	{
		f_ = std::move(func);
	}
};

}
