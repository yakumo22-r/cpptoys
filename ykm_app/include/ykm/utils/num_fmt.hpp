#include <fmt/format.h>

#include "num.hpp"

template <typename T>
struct fmt::formatter<ykm::app::num_xy<T>>
{
    constexpr auto parse(fmt::format_parse_context& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const ykm::app::num_xy<T>& ms, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "({}, {})", ms.x, ms.y);
    }
};

template <typename T>
struct fmt::formatter<ykm::app::num_xyz<T>>
{

    constexpr auto parse(fmt::format_parse_context& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const ykm::app::num_xyz<T>& ms, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "({}, {}, {})", ms.x, ms.y, ms.z);
    }
};
