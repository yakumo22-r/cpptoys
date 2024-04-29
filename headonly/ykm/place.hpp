#ifndef YKM_PLACE_HPP
#define YKM_PLACE_HPP 
#include <utility>

namespace ykm
{

template <typename C>
struct place final
{
  public:
    place() { set_null(true); }

    place(place<C>&& r)
    {
        if (r)
        {
            memcpy(buffer, r.buffer, sizeof(C));
            set_null(false);
            r.set_null(true);
        }
    }

    place(const place<C>& r)
    {
        if (r)
        {
            const C& rc = *((C*)r.buffer);
            construct(rc);
        }
    }

    place<C>& operator=(place<C>&& r)
    {
        if (!is_null())
            destruct();
        if (r)
        {
            memcpy(buffer, r.buffer, sizeof(C));
            set_null(false);
            r.set_null(true);
        }
        return *this;
    }

    place<C>& operator=(const place<C>& r)
    {
        if (!is_null())
            destruct();
        if (r)
        {
            const C& rc = *((C*)r.buffer);
            construct(rc);
        }
        return *this;
    }

    template <typename... Args>
    C* construct(Args... args)
    {
        C* c = new (get()) C(std::forward<Args>(args)...);
        set_null(false);
    }

    template <typename... Args>
    C* reconstruct(Args... args)
    {
        if (!is_null())
        {
            ref()->~C();
            set_null(false);
        }
        C* c = new (get()) C(std::forward<Args>(args)...);
    }
    void destruct() { ref()->~C(); }

    void* get_buffer() { return buffer; }
    const void* get_buffer() const { return buffer; }

    constexpr int size() const { return sizeof(C); }

    C* get() { return (C*)get_buffer(); }
    const C* get() const { return (C*)get_buffer(); }

    C& ref() { return *get(); }
    const C& ref() const { return *get(); }

    C* operator->() { return get(); }
    const C* operator->() const { return get(); }

    operator C&() { return ref(); }
    operator const C&() { return ref(); }

    operator bool() const { return !is_null(); }

    ~place()
    {
        if (!is_null())
        {
            destruct();
        }
    }

  private:
    char buffer[sizeof(C) + 1];
    bool is_null() const { return buffer[sizeof(C)]; }
    void set_null(char b) { buffer[sizeof(C)] = b; }
};

}
#endif
