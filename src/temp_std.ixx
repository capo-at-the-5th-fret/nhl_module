// module;

// #ifdef __cpp_lib_modules
//     #warning "import std; is available, use it instead of std.ixx"
// #endif

// #ifdef __cpp_lib_print
//     #warning "<print> is available, use it instead of custom print"
// #endif

export module temp_std;

export import <algorithm>;
export import <array>;
export import <chrono>;
export import <compare>;
export import <cassert>;
export import <cstddef>;
export import <cstdint>;
export import <execution>;
export import <format>;
export import <functional>;
export import <iostream>;
export import <map>;
export import <numeric>;
export import <optional>;
export import <random>;
export import <ranges>;
export import <regex>;
export import <set>;
export import <span>;
export import <string_view>;
export import <string>;
export import <thread>;
export import <type_traits>;
export import <unordered_map>;
export import <unordered_set>;
export import <utility>;
export import <vector>;
export import <version>;

export namespace temp
{
    template <typename... Args>
    void print(std::format_string<Args...> fmt, Args&&... args)
    {
        std::cout << std::format(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void println(std::format_string<Args...> fmt, Args&&... args)
    {
        std::cout << std::format(fmt, std::forward<Args>(args)...) << "\n";
    }
}
