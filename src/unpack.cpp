#include "unpack.hpp"

#include "types/csb.hpp"

auto ceu::unpack(const std::filesystem::path &file, const std::filesystem::path &out_path)
    -> unpack_result
{
    const auto ext = file.extension().string();

    // clang-format off
    switch (stringUnpackType[ext]) {
    case CSB:   return types::csb::unpack(file, out_path);
    default:    return FAIL;
    }
    // clang-format on
}
