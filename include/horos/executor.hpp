#ifndef HOROS_EXECUTOR_HPP
#define HOROS_EXECUTOR_HPP

#include <queue>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <iostream>

namespace horos {

class Executor {

public:
    Executor(): stop_(false) {
        worker_thread_ = std::thread(&Executor::run, this);
    }

    ~Executor() {
        stop_ = true;
        condition_.notify_all();

        if (worker_thread_.joinable()) {
            worker_thread_.join();
        }
    }

    void add_task(std::function<void()> task) {
        {
            std::lock_guard<std::mutex> lock(queue_mutex_);
            tasks_.push(task);
        }

        condition_.notify_one();
    }

private:
    void run() {
        while (!stop_) {
            std::function<void()> task;

            {
                std::unique_lock<std::mutex> lock(queue_mutex_);

                condition_.wait(lock, [this] {
                    return stop_ || !tasks_.empty();
                });

                if (stop_ && tasks_.empty()) { return; }

                task = std::move(tasks_.front());

                tasks_.pop();
            }

            if (task) { task(); }
        }
    }

private:
    std::queue<std::function<void()>> tasks_;
    std::mutex queue_mutex_;
    std::condition_variable condition_;
    std::thread worker_thread_;
    std::atomic<bool> stop_;
};

} // namespace horos

#endif // HOROS_EXECUTOR_HPP