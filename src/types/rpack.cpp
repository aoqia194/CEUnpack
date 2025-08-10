#include "rpack.hpp"

#include "../util.hpp"

#include "spdlog/spdlog.h"

#include <array>

auto ceu::types::rpack::unpack(const std::filesystem::path &file,
    const std::filesystem::path &out_path) -> unpack_result
{
    auto in_stream = std::ifstream(file, std::ios::binary);
    if (!in_stream.good()) {
        spdlog::error("Getting ifstream for file failed.", file.filename().string());
        return FAIL;
    }

    std::array<char, 4> magic{};
    util::read_into(in_stream, magic);
    if (strncmp(magic.data(), "RP6L", magic.size()) != 0) {
        spdlog::error("({}) is not a valid rpack format or is not supported.",
            magic.data());
        return FAIL;
    }
    in_stream.seekg(0x00, std::ios::beg);

    // TODO: Below applies for only RP6L currently.

    header header{};
    util::read_into(in_stream, header);

    std::vector<section> sections{};
    sections.resize(header.section_count);
    util::read_into(in_stream, sections);

    std::vector<filepart> parts{};
    parts.resize(header.part_count);
    util::read_into(in_stream, parts);

    std::vector<filemap> maps{};
    maps.resize(header.file_count);
    util::read_into(in_stream, maps);

    std::vector<uint32_t> nametable_offsets{};
    nametable_offsets.resize(header.name_table_count);
    util::read_into(in_stream, nametable_offsets);

    const auto nametable_start = in_stream.tellg();

    std::vector<std::array<char, 64>> nametable_names{};
    nametable_names.resize(header.name_table_count);
    for (size_t i = 0; i < header.name_table_count; ++i) {
        in_stream.seekg(static_cast<uint32_t>(nametable_start) + nametable_offsets[i],
            std::ios::beg);
        util::read_into(in_stream, nametable_names[i]);
    }

    for (size_t i = 0; i < header.file_count; ++i) {
        const auto filename = fmt::format("{}.{}", nametable_names[i].data(),
            filetype_string[static_cast<file_type>(maps[i].filetype)]);
        const auto out = out_path / filename;
        auto out_stream = std::ofstream(out, std::ios::binary);
        if (!out_stream.good()) {
            spdlog::error("Getting ofstream for ({}) failed.", filename);
            return FAIL;
        }

        size_t bytes = 0;

        const auto &map = maps[i];
        for (size_t j = 0; j < map.part_count; ++j) {
            const auto &part = parts[j];
            const auto &section = sections[part.section_idx];
            in_stream.seekg(section.offset + part.offset, std::ios::beg);

            std::vector<uint8_t> data{};
            data.resize(part.unpacked_size);
            util::read_into(in_stream, data);
            util::write_from(out_stream, data);
            bytes += part.unpacked_size;
        }

        out_stream.close();
        spdlog::debug("Wrote {} bytes to ({})", bytes, out.string());
    }

    in_stream.close();

    return OK;
}
