#ifndef YKM_APP_UTILS_NUM_HPP
#define YKM_APP_UTILS_NUM_HPP


#include <cstdint>

namespace ykm::app
{

template <typename T>
struct num_xy final
{
    T x;
    T y;

    bool operator==(num_xy r) const { return x == r.x && y == r.y; }
    bool operator!=(num_xy r) const { return x != r.x && y != r.y; }

    num_xy operator+(num_xy r) const { return {x + r.x, y + r.y}; }
    num_xy operator-(num_xy r) const { return {x - r.x, y - r.y}; }
    num_xy operator*(num_xy r) const { return {x * r.x, y * r.y}; }
    num_xy operator/(num_xy r) const { return {x / r.x, y / r.y}; }

    num_xy operator+(T v) const { return {x + v, y + v}; }
    num_xy operator-(T v) const { return {x - v, y - v}; }
    num_xy operator*(T v) const { return {x * v, y * v}; }
    num_xy operator/(T v) const { return {x / v, y / v}; }
};

using f_xy = num_xy<float>;
using d_xy = num_xy<double>;
using i_xy = num_xy<int>;
using i32_xy = num_xy<int32_t>;
using i64_xy = num_xy<int64_t>;

template <typename T>
struct num_xyz final
{
    T x;
    T y;
    T z;

    bool operator==(num_xyz r) const { return x == r.x && y == r.y && z == r.z; }
    bool operator!=(num_xyz r) const { return x != r.x && y != r.y && z != r.z; }

    num_xyz operator+(num_xyz r) const { return {x + r.x, y + r.y, z + r.z}; }
    num_xyz operator-(num_xyz r) const { return {x - r.x, y - r.y, z - r.z}; }
    num_xyz operator*(num_xyz r) const { return {x * r.x, y * r.y, z * r.z}; }
    num_xyz operator/(num_xyz r) const { return {x / r.x, y / r.y, z / r.z}; }

    num_xyz operator+(T v) const { return {x + v, y + v, z + v}; }
    num_xyz operator-(T v) const { return {x - v, y - v, z - v}; }
    num_xyz operator*(T v) const { return {x * v, y * v, z * v}; }
    num_xyz operator/(T v) const { return {x / v, y / v, z / v}; }
};

using f_xyz = num_xyz<float>;
using d_xyz = num_xyz<double>;
using i_xyz = num_xyz<int>;
using i32_xyz = num_xyz<int32_t>;
using i64_xyz = num_xyz<int64_t>;

}; // namespace ykm::app

#endif
