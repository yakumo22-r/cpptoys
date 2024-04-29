#ifndef YKM_THREAD_TOOL_HPP
#define YKM_THREAD_TOOL_HPP
#include <atomic>
#include <condition_variable>
#include <cstdio>
#include <iostream>
#include <mutex>
#include <queue>
#include <utility>

namespace ykm
{

template <typename T>
struct LockQueue final
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

//    T peek() const
//    {
//        std::unique_lock<std::mutex> lock(mut);
//        T value = m_queue.front();
//        return value;
//    }
//
//    bool empty() const
//    {
//        std::unique_lock<std::mutex> lock(mut);
//        return m_queue.empty();
//    }

    bool try_pop(T& t)
    {
        std::unique_lock<std::mutex> lock(mut);

        if (m_queue.empty())
        {
            return false;
        }

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
