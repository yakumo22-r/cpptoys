#ifndef YKM_THREAD_HPP
#define YKM_THREAD_HPP
#include <condition_variable>
#include <mutex>
#include <queue>
#include <utility>

namespace ykm
{

template <typename T>
struct squeue final
{
    void push(T&& t)
    {
        {
            std::unique_lock<std::mutex> lock(mut);
            m_queue.push(std::move(t));
        }
        cond.notify_one();
    }

    void push(const T& t)
    {
        {
            std::unique_lock<std::mutex> lock(mut);
            m_queue.push(t);
        }
        cond.notify_one();
    }

    bool empty() const
    {
        std::unique_lock<std::mutex> lock(mut);
        return m_queue.empty();
    }

    bool try_pop(T& t)
    {
        std::unique_lock<std::mutex> lock(mut);

        if (m_queue.empty())
            return false;

        t = std::move(m_queue.front());
        m_queue.pop();
        return true;
    }

    T pop()
    {
        std::unique_lock<std::mutex> lock(mut);
        cond.wait(lock, [this] { return !m_queue.empty(); });
        T value(std::move(m_queue.front()));
        m_queue.pop();
        return value;
    }

  private:
    std::queue<T> m_queue;
    mutable std::mutex mut;
    std::condition_variable cond;
};

} // namespace ykm

#endif
