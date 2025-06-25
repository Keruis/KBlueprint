#ifndef BLUEPRINT_THREADPOOL_H
#define BLUEPRINT_THREADPOOL_H

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>

class ThreadPool {
    struct TaskWrapper {
        std::size_t priority;
        std::function<void()> func;

        bool operator<(const TaskWrapper& other) const {
            return priority < other.priority;
        }
    };
public:
    explicit ThreadPool(std::size_t initCount, std::size_t maxCount);
    ~ThreadPool();

    template<class F, class... Args>
    auto submit(F&& f, Args&&... args)
    -> std::future<typename std::invoke_result<F, Args...>::type>;

    template<class F, class... Args>
    auto submit(int priority, F&& f, Args&&... args)
    -> std::future<typename std::invoke_result<F, Args...>::type>;

private:
    void createWorker() noexcept;

private:
    std::size_t maxThreads;
    std::atomic<std::size_t > currentThreads;
    std::atomic<std::size_t > idleThreads;
    std::vector<std::thread> workers;
    std::priority_queue<TaskWrapper> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> acceptTasks;
    std::atomic<bool> stop;
};

ThreadPool::ThreadPool(std::size_t initCount, std::size_t maxCount)
        : stop(false), acceptTasks(true), currentThreads(0), maxThreads(maxCount) {
    for (size_t i = 0; i < initCount; ++i) {
        createWorker();
    }
}

ThreadPool::~ThreadPool() {
    stop = true;
    acceptTasks = false;
    condition.notify_all();
    for (std::thread &worker : workers)
        worker.join();
}

template<class F, class... Args>
auto ThreadPool::submit(F&& f, Args&&... args)
-> std::future<typename std::invoke_result<F, Args...>::type> {
    return submit(0, std::forward<F>(f), std::forward<Args>(args)...);
}

template<class F, class ...Args>
auto
ThreadPool::submit(int priority, F &&f, Args &&...args) -> std::future<typename std::invoke_result<F, Args...>::type> {
    using return_type = typename std::invoke_result<F, Args...>::type;

    if (!acceptTasks) throw std::runtime_error("ThreadPool is shutting down");

    auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<return_type> res = task->get_future();

    {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.emplace(TaskWrapper{
                priority,
                [task] { (*task)(); }
        });

        if (idleThreads == 0 && currentThreads < maxThreads) {
            createWorker();
        }
    }
    condition.notify_one();
    return res;
}

void ThreadPool::createWorker() noexcept {
    std::thread worker([this] {
        while (true) {
            std::function<void()> task;

            {
                std::unique_lock<std::mutex> lock(queueMutex);

                if (stop && tasks.empty()) {
                    --currentThreads;
                    return;
                }

                ++idleThreads;

                bool hasTask = condition.wait_for(lock, std::chrono::seconds(10), [this] {
                    return stop || !tasks.empty();
                });

                --idleThreads;

                if (!hasTask && !stop) {
                    --currentThreads;
                    return;
                }

                if (stop && tasks.empty()) {
                    --currentThreads;
                    return;
                }

                task = std::move(tasks.top().func);
                tasks.pop();
            }

            task();
        }
    });

    {
        std::lock_guard<std::mutex> lock(queueMutex);
        workers.emplace_back(std::move(worker));
        ++currentThreads;
    }
}

#endif //BLUEPRINT_THREADPOOL_H
