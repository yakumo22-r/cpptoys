#ifndef YKM_SERPACK_HPP
#define YKM_SERPACK_HPP
#include <bit>
#include <codecvt>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>
#include <utility>
#include <vector>

namespace ykm
{

inline void meminv_cpy(void* target, const void* src, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        ((char*)target)[i] = ((const char*)src)[size - i - 1];
}

inline void meminv_set(void* p, size_t size)
{
    for (size_t i = 0; i < (size / 2); ++i)
    {
        char value = ((char*)p)[i];
        ((char*)p)[i] = ((const char*)p)[size - i - 1];
        ((char*)p)[size - i - 1] = value;
    }
}

struct packmeta
{
    static packmeta read(const char* data)
    {
        packmeta m;
        m.meta[0] = data[0];
        m.meta[1] = data[1];
        m.meta[2] = data[2];
        m.meta[3] = data[3];

        if (packsize_v & m.meta[0])
        {
            if (m.cmp_endian())
                memcpy(m.meta + 4, data + 4, 8);
            else
                meminv_cpy(m.meta + 4, data + 4, 8);
        }
        return m;
    }

    inline static constexpr size_t size = 16;
    // 8bit mem
    enum : unsigned char
    {
        litendian_v /*** mask              */ = 0b10000000,
        packsize_v /**** mask              */ = 0b01000000,
    };
    // 8bit int of mem aglin size
    // 8bit int of big ver
    // 8bit int of ver
    // 64bit int of pack size

    void write(const char* data)
    {
        meta[0] = data[0];
        meta[1] = data[1];
        meta[2] = data[2];
        meta[3] = data[3];

        if (packsize_v & meta[0])
        {
            if (cmp_endian())
                memcpy(meta + 4, data + 4, 8);
            else
                meminv_cpy(meta + 4, data + 4, 8);
        }
    }

    packmeta& set_endian(std::endian endian)
    {
        if (endian == std::endian::little)
            meta[0] |= litendian_v;
        else
            meta[0] &= ~litendian_v;
        return *this;
    }

    std::endian get_endian() const { return meta[0] & litendian_v ? std::endian::little : std::endian::big; }
    bool cmp_endian() const { return get_endian() == std::endian::native; }

    packmeta& set_align(uint8_t align)
    {
        meta[1] = align;
        return *this;
    }

    uint8_t get_align() const { return meta[1]; }

    packmeta& set_ver(uint8_t big, uint8_t ver)
    {
        meta[2] = big;
        meta[3] = ver;
        return *this;
    }

    uint8_t get_ver() const { return meta[3]; }
    uint8_t get_big_ver() const { return meta[2]; }

    packmeta& set_packsize(uint64_t pack_size)
    {
        if (pack_size == 0)
            meta[0] &= ~packsize_v;
        else
        {
            if (cmp_endian())
                memcpy(meta + 4, &pack_size, 8);
            else
                meminv_cpy(meta + 4, &pack_size, 8);
            meta[0] |= packsize_v;
        }
        return *this;
    }

    uint64_t get_packsize() const
    {
        uint64_t size;
        if (cmp_endian())
            memcpy(&size, meta + 4, 8);
        else
            meminv_cpy(&size, meta + 4, 8);
        return size;
    }

    packmeta()
    {
        struct __align
        {
            char a;
            int b;
            void* c;
        };
        set_endian(std::endian::native);
        set_align(alignof(__align));
        set_ver(0, 1);
        set_packsize(0);
    }

  private:
    uint8_t meta[size];
};

enum pknum : uint8_t
{
    unsign_v /* */ = 0b10000000,
    i8 /*       */ = 0b01000001,
    i16 /*      */ = 0b01000010,
    i32 /*      */ = 0b01000100,
    i64 /*      */ = 0b01001000,
    i128 /*     */ = 0b01010000,
    ibig /*     */ = 0b01000000,
    f32 /*      */ = 0b00100100,
    f64 /*      */ = 0b00101000,
    f128 /*     */ = 0b00100000,
    fbig /*     */ = 0b00100000,
    sizemask /*  */ = 0b00011111
};

struct packtype
{
    inline static constexpr size_t size = 4;
    // 8bit header
    enum : uint8_t
    {
        ukn /* unknow            */ = 0b10000000,
        num /* number            */ = 1,
        str /* string            */ = 2,
        buf /* buffer            */ = 3,
        tbl /* nv with iv        */ = 4,
        nv /*  name with any     */ = 6,
        arr /* array of num      */ = 7,
        iv /*  id with any       */ = 8,
        comp /* c struct         */ = 9,
    };

    // 8bit number type for { num | iv | arr }, see pknum | {unknow|buffer|string size 1-8 bit}
    // 8bit of {unknow|buffer|string size 9-16 bit}
    // 8bit of {unknow|buffer|string size 17-24 bit}

    uint32_t get_size() const
    {
    }
  private:
    uint8_t meta[size];
};

// wrapper

struct packdata
{
    char* buffer = nullptr;
    uint32_t size = 0;
    static constexpr uint32_t head = sizeof(uint32_t);
    static constexpr packdata* emtplc = nullptr;
};

struct packcstr
{
    const char* str;
    uint32_t size;
    static constexpr uint32_t head = sizeof(uint32_t);
    static constexpr packcstr* emtplc = nullptr;

    packcstr() : str(nullptr), size(0) {}
    packcstr(const char* str) : str(str), size(str ? strlen(str) : 0) {}
};

template <typename T>
using pack_rmcrp = std::remove_pointer_t<std::remove_reference_t<std::remove_const_t<T>>>;

template <typename T>
constexpr bool is_pack_num_t = std::is_integral_v<T> || std::is_floating_point_v<T>;

struct serpack
{
    // type
    // enum : uint8_t
    //{
    //    tbl /*  */ = 0,
    //    numi /* any integer */ = 1,
    //    numf /* any float   */ = 2,
    //    str /*  const char* */ = 3,
    //    buffer = 4,
    //    arr = 5,
    //    arrv = 6,
    //};

    // fmt mask
    // enum : uint16_t
    //{
    //    none /***** no meta data            */ = 0b00000000,
    //    id16 /***** 64bit id                */ = 0b00000001,
    //    id /***** 64bit id                  */ = 0b00000011,
    //    id64 /***** 64bit id                */ = 0b00000111,
    //    id128 /**** 128bit id of this data  */ = 0b00001111,
    //    hasid /**** valid id is open        */ = 0b00001111,
    //    name /***** str of name             */ = 0b00010000,
    //    namesize /* 8bit sizeof str         */ = 0b00110000,
    //    index /**** index of arr            */ = 0b01000000,
    //    typed /**** has type int next value */ = 0b10000000,
    //    numd /**** data nums                */ = 0b100000000,
    //};

    serpack() = default;
    serpack(serpack&& r) = default;
    serpack(serpack& r) : serpack(std::move(r)) {}
    serpack& operator=(serpack&& r) = default;
    serpack& operator=(serpack& r) { return this->operator=(std::move(r)); }

    ~serpack() { clear(); }

    void copy_to(serpack& r) const
    {
        for (auto d : storages)
        {
            packdata rd;
            rd.size = d.size;
            rd.buffer = new char[rd.size];
            memcpy(rd.buffer, d.buffer, rd.size);
            r.storages.push_back(rd);
        }
    }

    serpack& clear()
    {
        for (auto d : storages)
            delete[] d.buffer;
        storages.clear();
        return *this;
    }

    template <typename Ty, typename... Args>
    serpack& push(Ty ty, Args... args)
    {
        uint32_t size = do_get_size(ty, args...);
        char* buffer = new char[size];
        storages.push_back({buffer, size});
        do_add_group(buffer, ty, args...);
        return *this;
    }

    serpack& dopack()
    {
        if (storages.size() > 1)
        {
            uint32_t size = 0;
            for (auto d : storages)
                size += d.size;

            char* buffer = new char[size];

            uint32_t offset = 0;
            for (auto d : storages)
            {
                memcpy(&buffer[offset], d.buffer, d.size);
                offset += d.size;
            }

            for (auto d : storages)
                delete[] d.buffer;

            storages.clear();
            storages.push_back({buffer, size});
        }
        return *this;
    }

    packdata get_data() { return storages.back(); }

    template <typename Ty, typename... Args>
    serpack& get_ref(Ty& ty, Args&... args)
    {
        do_get_group(storages.back().buffer, &ty, &args...);
        return *this;
    }

    template <typename Ty, typename... Args>
    serpack& get(Ty ty, Args... args)
    {
        do_get_group(storages.back().buffer, ty, args...);
        return *this;
    }

  private:
    std::vector<packdata> storages;

  private:
    template <typename Ty, typename... Args>
    uint32_t do_add_group(char* buffer, Ty ty, Args... args)
    {
        uint32_t size = add(ty, buffer);
        if constexpr (sizeof...(args) > 0)
            size += do_add_group(&buffer[size], args...);

        return size;
    }

    template <typename Ty>
    static void ref_construct(void* s, void* t)
    {
        *((Ty*)t) = *((Ty*)s);
    }

    template <typename Ty>
    static uint32_t add(Ty t, char* buffer)
    {
        using Type = std::remove_const_t<std::remove_pointer_t<std::remove_reference_t<Ty>>>;
        uint32_t size = get_size(t);
        if constexpr (std::is_same_v<Type, packdata>)
        {
            ref_construct<uint32_t>(size, buffer);
            if constexpr (std::is_pointer_v<Ty>)
                memcpy(&buffer[packdata::head], t->buffer, t->size);
            else
                memcpy(&buffer[packdata::head], t.buffer, t.size);
        }
        if constexpr (std::is_same_v<Type, packcstr>)
        {
            ref_construct<uint32_t>(&size, buffer);
            if constexpr (std::is_pointer_v<Ty>)
                memcpy(&buffer[packcstr::head], t->str, t->size);
            else
                memcpy(&buffer[packcstr::head], t.str, t.size);
        }
        else if constexpr (std::is_pointer_v<Ty>)
            ref_construct<Type>(t, buffer);
        else
            ref_construct<Type>(&t, buffer);

        return size;
    }

    template <typename Ty>
    static void* get_pointer(Ty t)
    {
        if constexpr (!std::is_pointer_v<Ty> && !std::is_reference_v<Ty>)
            return nullptr;
        else if constexpr (std::is_pointer_v<Ty>)
            return t;
        else
            return &t;
    }

    template <typename Ty>
    static uint32_t get_size(Ty t)
    {
        using Type = std::remove_const_t<std::remove_pointer_t<std::remove_reference_t<Ty>>>;
        if constexpr (std::is_same_v<Type, packdata>)
            if constexpr (std::is_pointer_v<Ty>)
                return packdata::head + t->size;
            else
                return packdata::head + t.size;
        if constexpr (std::is_same_v<Type, packcstr>)
            if constexpr (std::is_pointer_v<Ty>)
                return packcstr::head + t->size;
            else
                return packcstr::head + t.size;
        else
            return sizeof(Type);
    }

    template <typename Ty, typename... Args>
    static uint32_t do_get_size(Ty ty, Args... args)
    {
        uint32_t size = get_size(ty);
        if constexpr (sizeof...(args) > 0)
            size += do_get_size(args...);
        return size;
    }

    template <typename Ty, typename... Args>
    static uint32_t do_get_group(char* buffer, Ty ty, Args... args)
    {
        uint32_t size = get_size(ty);

        using Type = pack_rmcrp<Ty>;

        if constexpr (std::is_same_v<Type, packdata>)
        {
            ref_construct<uint32_t>(buffer, &size);
            Type* p = nullptr;
            if constexpr (std::is_same_v<Ty, packdata>)
            {
                p = &ty;
                if (p->buffer)
                    memcpy(p->buffer, buffer, p->size);
                p = nullptr;
            }
            else if constexpr (std::is_same_v<Ty, packdata*>)
                p = ty;
            else if constexpr (std::is_same_v<Ty, packdata&>)
                p = &ty;

            if (p)
            {
                if (p->buffer)
                    memcpy(p->buffer, &buffer[packdata::head], p->size);
                else
                {
                    p->buffer = &buffer[packdata::head];
                    p->size = size;
                }
            }
        }
        else if constexpr (std::is_same_v<Type, packcstr>)
        {
            ref_construct<uint32_t>(buffer, &size);
            Type* p = nullptr;
            if constexpr (std::is_same_v<Ty, packcstr*>)
                p = ty;
            else if constexpr (std::is_same_v<Ty, packcstr&>)
                p = &ty;

            if (p)
            {
                p->str = &buffer[packcstr::head];
                p->size = size;
            }
        }
        else if (void* p = get_pointer(ty))
        {
            ref_construct<Type>(buffer, p);
        }

        if constexpr (sizeof...(args) > 0)
            size += do_get_group(&buffer[size], args...);
        return size;
    }
};

} // namespace ykm

template <typename T>
ykm::serpack ykm_serpack_tbl(const T* t)
{
    return ykm_serpack(*t);
}

template <typename T>
ykm::serpack ykm_serpack_tbl(const T& t)
{
    ykm::serpack pack;
    return pack.push(t);
}

template <typename T>
T ykm_unpack_tbl(ykm::serpack& packer)
{
    T t;
    packer.get(&t);
    return t;
}

#endif
