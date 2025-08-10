#ifndef CEUNPACK_EXTRACTOR_HPP
#define CEUNPACK_EXTRACTOR_HPP

#include <filesystem>
#include <string_view>
#include <unordered_map>

namespace ceu
{
    enum unpack_type : int8_t
    {
        INVALID = -1,
        CSB,
        SPB,
        RPACK,
    };

    inline std::unordered_map<std::string_view, unpack_type> stringUnpackType = {
        {     "", INVALID},
        {  "csb",     CSB},
        {  "spb",     SPB},
        {"rpack",   RPACK}
    };

    inline std::unordered_map<unpack_type, std::string_view> unpackTypeString = {
        {INVALID,      ""},
        {    CSB,   "csb"},
        {    SPB,   "spb"},
        {  RPACK, "rpack"}
    };

    enum unpack_result : int8_t
    {
        FAIL = -1,
        OK,
    };

    inline std::unordered_map<std::string_view, unpack_result> stringUnpackResult = {
        {"FAIL", FAIL},
        {  "OK",   OK},
    };

    inline std::unordered_map<unpack_result, std::string_view> unpackResultString = {
        {FAIL, "FAIL"},
        {  OK,   "OK"},
    };

    auto unpack(const std::filesystem::path &file, const std::filesystem::path &out_path)
        -> unpack_result;
} // namespace ceu

#endif // CEUNPACK_EXTRACTOR_HPP
