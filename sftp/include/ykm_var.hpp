#ifndef YKM_OPT_HPP
#define YKM_OPT_HPP
#include <cstddef>
#include <utility>
#include <vector>
namespace ykm
{

template <typename C>
struct place final
{
  public:
    template <typename... Args>
    C* construct(Args... args)
    {
        C* c = new (buffer) C(std::forward<Args>(args)...);
        isNull = false;
    }

    void destruct() { ((C*)buffer)->~C(); }

    void* get_buffer() { return buffer; }

    const void* get_buffer() const { return buffer; }

    constexpr int get_size() const { return sizeof(C); }

    C& ref() { return *((C*)buffer); }
    const C& ref() const { return *((C*)buffer); }

    C* get() { return (C*)buffer; }
    const C* get() const { return (C*)buffer; }

    C* operator->() { return get(); }
    const C* operator->() const { return get(); }

    operator C&() { return V(); }
    operator const C&() { return V(); }

    operator bool( const { return !isNull; }

    place() : isNull(true) {}

    place(place<C>&& r)
    {
        if (r)
        {
            memcpy(buffer, r.buffer, sizeof(C));
            isNull = false;
            r.isNull = true;
        }
    }

    place(const place<C>& r)
    {
        if (r)
        {
            const C& rc = *((C*)r.buffer);
            Construct(rc);
        }
    }

    place<C>& operator=(place<C>&& r)
    {
        if (!isNull)
            Destruct();
        if (r)
        {
            memcpy(buffer, r.buffer, sizeof(C));
            isNull = false;
            r.isNull = true;
        }
        return *this;
    }

    place<C>& operator=(const place<C>& r)
    {
        if (!isNull)
            Destruct();
        if (r)
        {
            const C& rc = *((C*)r.buffer);
            Construct(rc);
        }
        return *this;
    }

  private:
    char buffer[sizeof(C)];
    char isNull = true;
};

//template <typename C, int S>
//struct placePool;
//
//template <typename C>
//struct placeComp final
//{
//    C& ref() { return *p; }
//    const C& ref() const { return *p; }
//
//    C* get() { return p; }
//    const C* get() const { p; }
//
//    C* operator->() { return p; };
//    const C* operator->() const { return p; };
//
//    operator C&() { return *p; }
//    operator const C&() const { return *p; }
//
//    operator bool() { return p != nullptr && _uuid == *(p_uuid); }
//    const;
//
//  private:
//    template <typename C, int S>
//    friend struct placePool;
//    int _uuid = 0;
//    int* p_uuid = nullptr;
//    C* p = nullptr;
//};
//
//template <typename C, int Size>
//struct placePool final
//{
//  public:
//    struct placeTuple
//    {
//        int uuid;
//        place<C> c;
//    };
//
//    placePool() : remain(Size) {
//        pool.push_back(&__first);
//    }
//
//    void resize(size_t size) { pool.resize(size); }
//    void reserve(size_t cap) { pool.reserve(cap); }
//    auto size() const { return pool.size(); }
//    auto begin() { return pool.begin(); }
//    auto end() { return pool.end(); }
//    auto front() { return pool.front(); }
//    auto back() { return pool.back(); }
//    auto operator[](size_t i) { return pool[i]; }
//    auto at(size_t i) { return pool[i]; }
//
//
//  public:
//    placeComp<C> push_back(const C& c)
//    {
//        auto& tup = get_free();
//        tup.c.construct(c);
//        tup.uuid = (int)(&tup);
//        return to_comp(tup);
//    }
//    template <typename... Args>
//    placeComp<C> emplace_back(Args... args)
//    {
//        auto& tup = get_free();
//        tup.c.construct(std::forward<Args>(args)...);
//        tup.uuid = (int)(&tup);
//        return to_comp(tup);
//    }
//    
//    bool valid_comp(placeComp<C> comp) const{
//        comp.p;
//    }
//
//  private:
//    using Tuple = char[sizeof(int) + sizeof(place<C>)];
//    using TupleBlock = char[sizeof(Tuple) * Size];
//
//    TupleBlock __first;
//    int remain;
//    std::vector<TupleBlock*> pool;
//    std::vector<Tuple*> emptyArr;
//  private:
//    placeTuple& get_free()
//    {
//        if (emptyArr.empty())
//            return &pool.push_back();
//        else
//        {
//            size_t i = empty_arr.back();
//            empty_arr.pop_back();
//            return pool.at(i);
//        }
//    }
//    placeComp<C> to_comp(placeTuple& tup)
//    {
//        placeComp<C> comp;
//        comp._uuid = tup.uuid;
//        comp.p = tup.c;
//        return comp;
//    }
//};
//
} // namespace ykm
#endif
