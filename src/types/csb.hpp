#ifndef CEUNPACK_CSB_HPP
#define CEUNPACK_CSB_HPP

#include "../unpack.hpp"

namespace ceu::types::csb
{
    struct vfsb_header
    {
        char filename[64]{};
        int32_t offset{};
        int32_t size{};
        int32_t unk0{};
        int32_t unk1{};
        int32_t unk2{};
        int32_t unk3{};
    };

    struct header
    {
        int32_t size{};
        int32_t fsb_count{};
        int32_t unk0{};
    };

    auto unpack(const std::filesystem::path &file, const std::filesystem::path &out_path)
        -> unpack_result;
} // namespace ceu::types::csb

#endif // CEUNPACK_CSB_HPP
