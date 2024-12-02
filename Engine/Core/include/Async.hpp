#pragma once

#include <functional>
#include <future>
#include <memory>
#include <thread>
#include <type_traits>

template <typename Function, typename... Args>
auto async(Function&& func,
           Args&&... args) -> std::future<typename std::result_of<Function(Args...)>::type>
{
    using return_type = typename std::result_of<Function(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<Function>(func), std::forward<Args>(args)...));

    std::future<return_type> result = task->get_future();
    std::thread([task]() { (*task)(); }).detach();
    return result;
}
