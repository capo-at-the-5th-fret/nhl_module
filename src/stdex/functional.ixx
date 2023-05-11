module;

#include <functional>

export module stdex:functional;

import :type_traits;

export namespace stdex
{
    namespace detail
    {
        template <typename T>
        void hash_combine_impl(std::size_t& hash_value, T const& t)
        {
            // 32-bit
            if constexpr (sizeof(std::size_t) == 4)
            {
                hash_value ^= std::hash<T>{}(t) + 0x9e3779b9U +
                                (hash_value << 6) + (hash_value >> 2);
            }
            // 64-bit
            else if constexpr (sizeof(std::size_t) == 8)
            {
                hash_value ^= std::hash<T>{}(t) + 0x9e3779b97f4a7c15LLU +
                                (hash_value << 12) + (hash_value >> 4);
            }
            else
            {
                static_assert(stdex::always_false_v<T>,
                                "The size of std::size_t is not supported by "
                                "hash_combine");
            }
        }
    }

    template <typename T, typename... Types>
    inline void hash_combine(std::size_t& hash_value, const T& t,
        const Types&... args)
    {
        detail::hash_combine_impl(hash_value, t);
        ((void)detail::hash_combine_impl(hash_value, args), ...);
    }

    template <typename T, typename... Types>
    std::size_t hash(T const& t, Types const&... args)
    {
        auto ret = std::hash<T>{}(t);

        if constexpr (sizeof...(args) > 0)
        {
            ((void)detail::hash_combine_impl(ret, args), ...);
        }

        return ret;
    }
}
