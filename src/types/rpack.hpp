#ifndef CEUNPACK_RPACK_HPP
#define CEUNPACK_RPACK_HPP

#include "../unpack.hpp"

namespace ceu::types::rpack
{
    enum file_type : uint8_t
    {
        UNKNOWN = 0,
        MSH = 16,
        TEX = 32,
        SHD = 48,
        ANM = 64,
        ANM2 = 66,
        FX = 80,
    };

    inline std::unordered_map<std::string_view, file_type> string_filetype = {
        {"unknown", UNKNOWN},
        {    "msh",     MSH},
        {    "tex",     TEX},
        {    "shd",     SHD},
        {    "anm",     ANM},
        {   "anm2",    ANM2},
        {     "fx",      FX},
    };

    inline std::unordered_map<file_type, std::string_view> filetype_string = {
        {UNKNOWN, "unknown"},
        {    MSH,     "msh"},
        {    TEX,     "tex"},
        {    SHD,     "shd"},
        {    ANM,     "anm"},
        {   ANM2,    "anm2"},
        {     FX,      "fx"},
    };

    struct filemap
    {
        uint8_t part_count;

        uint8_t unk0;

        uint8_t filetype;

        uint8_t unk1;

        uint32_t file_idx;

        //! The starting offset of the first part in the map.
        uint32_t first_part;
    };

    struct filepart
    {
        //! 0 to (section_count - 1)
        uint8_t section_idx;

        uint8_t unk0;

        uint16_t file_idx;

        //! Relative to section offset.
        uint32_t offset;

        uint32_t unpacked_size;

        //! 0 means not packed.
        uint32_t packed_size;
    };

    struct section
    {
        file_type filetype;

        uint8_t unk0;

        uint8_t unk1;

        uint8_t unk2;

        //! From base address/SOF.
        uint32_t offset;

        //! Excluding 0x00.
        uint32_t unpacked_size;

        //! Excluding 0x00.
        uint32_t packed_size;

        uint32_t part_count;
    };

    struct header
    {
        char magic[4];

        uint32_t version;

        // 0 = uncompressed, 1 = zlib, the rest unknown.
        uint32_t compression_type;

        uint32_t part_count;

        uint32_t section_count;

        uint32_t file_count;

        uint32_t name_table_size;

        //! Count of all the filename strings in the table.
        //! Mostly the same as file_count
        uint32_t name_table_count;

        uint32_t block_size;
    };

    auto unpack(const std::filesystem::path &file, const std::filesystem::path &out_path)
        -> unpack_result;
} // namespace ceu::types::rpack

#endif // CEUNPACK_RPACK_HPP
