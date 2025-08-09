#include "util.hpp"

#include <algorithm>
#include <stdexcept>

namespace ceu::util
{
    auto lowercase(std::string str) -> std::string
    {
        std::ranges::transform(str, str.begin(),
            [](const unsigned char c) { return std::tolower(c); });
        return str;
    }

    template <typename T>
    T get_data(const uint8_t *data, const size_t offset, const size_t data_size)
    {
        static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

        if (offset + sizeof(T) > data_size) {
            throw std::out_of_range("Attempt to read past end of data");
        }

        T value;
        std::memcpy(&value, data + offset, sizeof(T));
        return value;
    }
} // namespace ceu::util
