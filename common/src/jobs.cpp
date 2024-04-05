#include <jobs.hpp>

namespace Common::Tools
{
JobQueue::JobQueue(const int size) : m_terminate(false)
{
    for (int i = 0; i < size; ++i)
    {
        m_threads.emplace_back([this]() {
            while (true)
            {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(m_tasks_mutex);
                    m_tasks_cv.wait(lock, [this]() { return m_terminate || !m_tasks.empty(); });
                    if (m_terminate && m_tasks.empty())
                    {
                        return;
                    }
                    task = m_tasks.front();
                    m_tasks.pop();
                }
                task();
            }
        });
    }
}

JobQueue::~JobQueue()
{
    {
        std::unique_lock<std::mutex> lock(m_tasks_mutex);
        m_terminate = true;
    }
    m_tasks_cv.notify_all();
    for (auto &thread : m_threads)
    {
        thread.join();
    }
}

} // namespace Common::Tools