#ifndef CEUNPACK_UTIL_HPP
#define CEUNPACK_UTIL_HPP

#include <string>

namespace ceu::util
{
    auto lowercase(std::string str) -> std::string;

    template <typename T>
    auto get_data(const uint8_t *data, size_t offset, size_t data_size) -> T;
} // namespace ceu::util

#endif // CEUNPACK_UTIL_HPP
