export module stdex:type_traits;

import <type_traits>;

namespace stdex
{
    template <typename... Ts>
    struct always_false : std::false_type
    {
    };

    template <typename... Ts>
    inline constexpr bool always_false_v = always_false<Ts...>::value;
}
