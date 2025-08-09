#ifndef CEUNPACK_CSB_HPP
#define CEUNPACK_CSB_HPP

#include "../unpack.hpp"

namespace ceu::types::csb
{
    struct vfsb_header
    {
        char filename[64];
        int32_t offset;
        int32_t size;

        int32_t unk0;
        int32_t unk1;
        int32_t unk2;
        int32_t unk3;
    };

    struct header
    {
        int32_t size;
        int32_t fsbCount;

        int32_t unk0;
    };

    struct main
    {
        uint8_t padding[64];
        header header;
        std::vector<vfsb_header> vfsb_headers;
        std::vector<std::vector<uint8_t>> vfsb_files;
    };

    auto unpack(const std::filesystem::path &file) -> unpack_result;
} // namespace ceu::types::csb

#endif // CEUNPACK_CSB_HPP
