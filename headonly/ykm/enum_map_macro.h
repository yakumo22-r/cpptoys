// clang-format off
#ifdef YKM_ENUM_E__
#undef YKM_ENUM_E__
#undef YKM_ENUM_EN_
#undef YKM_ENUM_EI_
#undef YKM_ENUM_ENI
#endif

#define YKM_ENUM_MAP_NS define_it_when_see_error
#define YKM_ENUM_E__(e) {YKM_ENUM_MAP_NS::e, #e},
#define YKM_ENUM_EN_(e, n) {YKM_ENUM_MAP_NS::e, n},
#define YKM_ENUM_EI_(e, i) {YKM_ENUM_MAP_NS::e, #e},
#define YKM_ENUM_ENI(e, n, i) {YKM_ENUM_MAP_NS::e, n},
