/*
    place object in stack object helper
    void* package
    date : 2024/5/6
    version : pub 0.0.1
*/

#ifndef YKM_PLACE_HPP
#define YKM_PLACE_HPP
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>
#include <typeinfo>
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

struct any_info final
{
    using destructor = void (*)(void* p);
    using mover = void (*)(void* src, void* target);
    using copier = void (*)(void* src, void* target);

    mover _move;
    copier _copy;
    destructor _des;
    size_t type;
    size_t size;

    any_info() : size(0) {}
};

inline void* any_convert_pp(void* tar)
{
    void* p;
    memcpy(&p, tar, sizeof(void*));
    return p;
}

template <typename T>
inline static constexpr bool any_int_type = std::is_integral_v<T> || std::is_enum_v<T>;

template <typename T>
inline static constexpr bool any_base_type = any_int_type<T> || std::is_floating_point_v<T> || std::is_pointer_v<T>;

template <typename T>
any_info* get_any_info()
{
    static any_info info;
    if (info.size > 0)
        return &info;

    info.size = sizeof(T);
    if constexpr (any_base_type<T>) // int float pointer
    {
        info._move = nullptr;
        info._copy = nullptr;
        info._des = nullptr;

        if constexpr (any_int_type<T>)
            info.type = typeid(int64_t).hash_code();
        else
            info.type = typeid(T).hash_code();
    }
    else
    {
        info._copy = [](void* tar, void* src) { *((T*)tar) = *((T*)src); };
        info._move = [](void* tar, void* src) { *((T*)tar) = std::move(*((T*)src)); };
        info._des = [](void* tar) { ((T*)tar)->~T(); };
        info.type = typeid(T).hash_code();
    }
    return &info;
}

// untested
template <size_t StackSize>
struct any_s final
{
    template <typename T>
    T* try_cast()
    {
        if constexpr (sizeof(T) <= stack_size())
            return (T*)(_info && typeid(T).hash_code() == _info->type ? buffer : nullptr);
        else
            return (T*)(_info && typeid(T).hash_code() == _info->type ? any_convert_pp(buffer) : nullptr);
    }

    template <typename T>
    const T* try_cast_const()
    {
        if constexpr (sizeof(T) <= stack_size())
            return (T*)(_info && typeid(T).hash_code() == _info->type ? buffer : nullptr);
        else
            return (T*)(_info && typeid(T).hash_code() == _info->type ? any_convert_pp(buffer) : nullptr);
    }

    any_s() : _info(nullptr) {}

    template <typename T>
    any_s& operator=(T t)
    {
        set<T>(std::forward(t));
        return *this;
    }

    template <typename T>
    any_s(T t)
    {
        set<T>(std::forward(t));
    }

    template <size_t SS>
    any_s& operator=(any_s<SS>&& r)
    {
        if (_info)
            destruct();

        _info = r._info;
        r._info = nullptr;
        if (!_info)
            return;

        void* p = any_s<SS>::stack_size() >= _info->size ? r.buffer : any_convert_pp(r.buffer);
        if constexpr (stack_size() >= any_s<SS>::stack_size())
        {
            memcpy(buffer, p, any_s<SS>::stack_size());
            if (any_s<SS>::stack_size() < _info->size)
                free(p);
            return *this;
        }
        else
        {
            if (stack_size() >= _info->size)
                memcpy(buffer, p, stack_size());
            else if (any_s<SS>::stack_size() >= _info->size)
            {
                void* m = malloc(_info->size);
                memcpy(m, r.buffer, _info->size);
                memcpy(buffer, &m, sizeof(void*));
            }
            else
            {
                memcpy(buffer, r.buffer, sizeof(void*));
            }
            return *this;
        }
    }

    template <size_t SS>
    any_s& operator=(any_s<SS>& r)
    {
        return this->operator=(std::move(r));
    }

    template <size_t SS>
    any_s(any_s<SS>&& r)
    {
        this->operator=(std::move(r));
    }

    template <size_t SS>
    any_s(any_s<SS>& r) : any_s(std::move(r)){};

    operator bool() const { return _info; }

    ~any_s() { destruct(); }

  protected:
    constexpr static size_t stack_size()
    {
        size_t min = sizeof(void*) > sizeof(int64_t) ? sizeof(void*) : sizeof(int64_t);
        return min > StackSize ? min : StackSize;
    }

    any_info* _info;
    unsigned char buffer[stack_size()];

    bool is_stack_storege() {}

    void destruct()
    {
        void* p = _info->size <= stack_size() ? buffer : any_convert_pp(buffer);
        if (_info->_des)
            _info->_des(p);

        if (_info->size > stack_size())
            free(p);
    }

    void move(void* src)
    {
        void* p = _info->size <= stack_size() ? buffer : any_convert_pp(buffer);
        if (_info->_move)
            _info->_move(p, src);
        else
            memcpy(p, src, _info->size);
    }
    void copy(void* src)
    {
        void* p = _info->size <= stack_size() ? buffer : any_convert_pp(buffer);
        if (_info->_copy)
            _info->_copy(p, src);
        else
            memcpy(p, src, _info->size);
    }

    template <typename T>
    void set(T t)
    {
        using Ty = std::remove_const_t<std::remove_reference_t<T>>;

        auto info = get_any_info<Ty, stack_size()>();

        if constexpr (any_base_type<Ty> && sizeof(Ty) <= stack_size()) // base type
        {
            if constexpr (any_int_type<Ty>)
            {
                int64_t i = t;
                memcpy(buffer, &i, sizeof(int64_t));
            }
            else
            {
                memcpy(buffer, &t, sizeof(Ty));
            }
        }
        else
        {
            if (_info && _info->type == info->type)
            {
                if constexpr (std::is_rvalue_reference_v<T>)
                    move(&t);
                else
                    copy(&t);
            }
            else if (_info)
            {
                destruct();
            }

            if constexpr (sizeof(Ty) <= stack_size()) // small struct
            {
                new (buffer) Ty(std::forward(t));
            }
            else // large struct
            {
                void* b = malloc(sizeof(Ty));
                Ty* v = new (v) Ty(std::forward(t));
                memcpy(buffer, &v, sizeof(Ty*));
            }
        }
        _info = info;
    }
};

using any = any_s<sizeof(int64_t)>;
using any_tiny = any_s<8>;
using any_small = any_s<16>;
using any_medium = any_s<32>;
using any_large = any_s<64>;
using any_big = any_s<128>;
using any_huge = any_s<256>;
using any_full = any_s<512>;
using any_super = any_s<1024>;

} // namespace ykm
#endif
