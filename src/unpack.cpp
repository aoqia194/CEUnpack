#include "unpack.hpp"

#include "types\csb.hpp"

namespace ceu
{
    auto unpack(const std::filesystem::path &file) -> unpack_result
    {
        const auto ext = file.extension().string();

        // clang-format off
        switch (stringUnpackType[ext]) {
        case CSB:   return types::csb::unpack(file);
        default:    return FAIL;
        }
        // clang-format on
    }
} // namespace ceu
