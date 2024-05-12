#ifndef YKM_PROXY_WRAP_HPP
#define YKM_PROXY_WRAP_HPP
#include "proxy.h"

namespace ykm
{

#define YKM_PROXY_FUNCS(...) PRO_MAKE_DISPATCH_PACK(__VA_ARGS__)
#define YKM_PROXY_MEMBER(F, ...) PRO_DEF_MEMBER_DISPATCH(F, __VA_ARGS__);

#define YKM_PROXY_I_DEF(ClassName, Packs, Funcs)                              \
    struct ClassName                                                          \
    {                                                                         \
        Funcs;                                                                \
        PRO_DEF_FACADE(INTERNAL_Facade, Packs);                               \
        using INTERNAL_Proxy = ::pro::proxy<INTERNAL_Facade>;                 \
                                                                              \
        template <typename... A>                                              \
        static INTERNAL_Proxy MakeProxy(A&&... a)                             \
        {                                                                     \
            using F = INTERNAL_Facade;                                        \
            return ::pro::make_proxy<F, A...>(std::forward<A>(a)...);         \
        }                                                                     \
                                                                              \
        template <typename... A>                                              \
        static INTERNAL_Proxy MakeProxyInplace(A&&... a)                      \
        {                                                                     \
            using F = INTERNAL_Facade;                                        \
            return ::pro::make_proxy_inplace<F, A...>(std::forward<A>(a)...); \
        }                                                                     \
    };                                                                        \
    using ClassName##_Facade = ClassName::INTERNAL_Facade;                    \
    using ClassName##_Proxy = ClassName::INTERNAL_Proxy

// #define YKM_PROXY_DEF_END(ClassName)

} // namespace ykm
#endif
