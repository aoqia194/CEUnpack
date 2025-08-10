#include "csb.hpp"

#include "../util.hpp"

#include "spdlog/spdlog.h"

auto ceu::types::csb::unpack(const std::filesystem::path &file,
    const std::filesystem::path &out_path) -> unpack_result
{
    auto in_stream = std::ifstream(file, std::ios::binary);
    if (!in_stream.good()) {
        spdlog::error("Getting ifstream for file failed.", file.filename().string());
        return FAIL;
    }

    // True CSB file starts 64 bytes after SOF.
    in_stream.seekg(0x40, std::ios::beg);

    header header{};
    util::read_into(in_stream, header);

    std::vector<vfsb_header> vfsb_headers{};
    vfsb_headers.resize(header.fsb_count);
    util::read_into(in_stream, vfsb_headers);

    std::vector<std::vector<uint8_t>> vfsb_data{};
    vfsb_data.resize(header.fsb_count);
    for (size_t i = 0; i < vfsb_data.size(); ++i) {
        vfsb_data[i].resize(vfsb_headers[i].size);
        util::read_into(in_stream, vfsb_data[i]);
    }

    in_stream.close();

    for (size_t i = 0; i < vfsb_headers.size(); ++i) {
        const auto out = out_path / fmt::format("{}.fsb", vfsb_headers[i].filename);
        auto out_stream = std::ofstream(out, std::ios::binary);
        if (!out_stream.good()) {
            spdlog::error("Getting ofstream for file failed.",
                out.filename().string());
            return FAIL;
        }

        util::write_from(out_stream, vfsb_data[i]);
        out_stream.close();

        spdlog::debug("Wrote {} bytes to ({})", vfsb_data[i].size(), out.string());
    }

    return OK;
}
