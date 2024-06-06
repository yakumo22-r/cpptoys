#ifndef YKM_ASYNC_MACHINE_HPP
#define YKM_ASYNC_MACHINE_HPP

#include <cstdint>
#include <list>
#include <chrono>

namespace ykm
{

struct async_state
{
    uint64_t frame;
    uint64_t time_ms;
};

class async_pip;

struct async_handle
{
  public:
    async_handle(uint32_t ms, uint32_t frame, bool bExit) //
        : wait_ms(ms), wait_frame(frame), bExit(bExit){};

    bool next(async_state state, async_pip* pip);

  private:
    uint32_t wait_ms;
    uint32_t wait_frame;
    bool bExit;
};

class async_pip
{
  protected:
    async_pip(async_handle (*wrapper)(async_pip*)) : wrapper(wrapper) {}

    template <typename Pip>
    async_handle async_next(async_handle (Pip::*func)())
    {
        set_next_func(func);
        return {0, 0, false};
    }
    template <typename Pip>
    async_handle async_wait(float time, async_handle (Pip::*func)())
    {
        set_next_func(func);
        return {(uint32_t)(time * 1000), 0, false};
    }

    template <typename Pip>
    async_handle async_wait(int ms, async_handle (Pip::*func)())
    {
        set_next_func(func);
        return {(uint32_t)ms, 0, false};
    }

    template <typename Pip>
    async_handle async_yield(uint32_t frame, async_handle (Pip::*func)())
    {
        set_next_func(func);
        return {0, frame, false};
    }

    template <typename Pip>
    async_handle async_final(async_handle (Pip::*func)())
    {
        auto wrap = memberfunction<Pip>{func};
        memcpy(&next_func, &wrap, sizeof(wrap));
        return {0, 0, true};
    }

  public:
    template <typename Pip>
    auto get_next_func() const
    {
        auto wrap = memberfunction<Pip>{};
        memcpy(&wrap, &next_func, sizeof(wrap));
        return wrap.func;
    }

  private:
    template <typename T>
    struct memberfunction
    {
        async_handle (T::*func)();
    };

    template <typename Pip>
    void set_next_func(async_handle (Pip::*func)())
    {
        auto wrap = memberfunction<Pip>{func};
        memcpy(&next_func, &wrap, sizeof(wrap));
    }

    async_handle (*wrapper)(async_pip*);
    char next_func[16];
    async_handle go_next() { return wrapper(this); }

    friend async_handle;
};

template <typename Pip>
class async_pip_wrap : public async_pip
{
  public:
    using async_handle = ykm::async_handle;
    async_pip_wrap() : async_pip([](async_pip* pip) { return (((Pip*)pip)->*(pip->get_next_func<Pip>()))(); }) {}
};

inline bool async_handle::next(async_state state, async_pip* pip)
{
    if (wait_ms <= state.time_ms && wait_frame <= state.frame)
    {
        *this = pip->go_next();
        wait_ms += state.time_ms;
        wait_frame += state.frame;
    }

    return bExit;
};

class async_machine final
{
  public:
    async_machine()
    {
        state.time_ms = 0;
        state.frame = 0;
        start_tp = std::chrono::high_resolution_clock::now();
    }

    template <typename Pip, typename... Args>
    async_machine& add_task(async_handle (Pip::*start)(), Args&&... args)
    {
        Pip* pip = new Pip(std::forward<Args>(args)...);
        tasks.push_back({[](void* p) { delete (Pip*)p; }, pip, (pip->*start)()});
        return *this;
    }

    void process_next()
    {
        ++state.frame;

        state.time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_tp).count();
        for (auto itr = tasks.begin(); itr != tasks.end();)
        {
            if (itr->hnd.next(state, itr->pip)) //
            {
                itr->release(itr->pip);
                itr = tasks.erase(itr);
            }
            else //
            {
                itr++;
            }
        }
    }

  private:
    using time_point = std::chrono::steady_clock::time_point;
    async_state state;
    struct task
    {
        void (*release)(void*);
        async_pip* pip;
        async_handle hnd;
    };
    std::list<task> tasks;
    time_point start_tp;
};

} // namespace ykm

#endif
