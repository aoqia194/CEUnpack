#ifndef CEUNPACK_UTIL_HPP
#define CEUNPACK_UTIL_HPP

#include "spdlog/spdlog.h"

#include <algorithm>
#include <fstream>
#include <string>

namespace ceu::util
{
    inline auto lowercase(std::string str) -> std::string
    {
        std::ranges::transform(str, str.begin(),
            [](const unsigned char c) { return std::tolower(c); });
        return str;
    }

    template <typename T>
    auto write_from(std::ofstream &stream, const std::vector<T> &data) -> void
    {
        static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

        // clang-tidy off
        stream.write(reinterpret_cast<const char *>(&data[0]), sizeof(T) * data.size());
        // clang-tidy on
    }

    template <typename T> auto write_from(std::ofstream &stream, const T &value) -> void
    {
        static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

        // clang-tidy off
        stream.write(reinterpret_cast<const char *>(value), sizeof(T));
        // clang-tidy on
    }

    template <typename T>
    auto read_into(std::ifstream &stream, std::vector<T> &data) -> void
    {
        static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

        // clang-tidy off
        stream.read(reinterpret_cast<char *>(&data[0]), sizeof(T) * data.capacity());
        // clang-tidy on
    }

    template <typename T> auto read_into(std::ifstream &stream, T &value) -> void
    {
        static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

        // clang-tidy off
        stream.read(reinterpret_cast<char *>(&value), sizeof(T));
        // clang-tidy on
    }
} // namespace ceu::util

#endif // CEUNPACK_UTIL_HPP
