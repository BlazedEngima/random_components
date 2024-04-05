#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

namespace Common::Tools
{

class JobQueue
{
  public:
    JobQueue(const int size);

    ~JobQueue();

    template <typename F, typename... Args> void enqueue(F &&f, Args &&...args)
    {
        {
            std::unique_lock<std::mutex> lock(m_tasks_mutex);
            m_tasks.emplace([f, args...]() { f(args...); });
        }
        m_tasks_cv.notify_one();
    }

  private:
    std::vector<std::thread> m_threads;
    std::queue<std::function<void()>> m_tasks;
    std::mutex m_tasks_mutex;
    std::condition_variable m_tasks_cv;
    bool m_terminate;
};

} // namespace Common
