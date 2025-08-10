#include "main.hpp"

#include "unpack.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"

#include "cxxopts.hpp"

auto main(const int argc, const char **argv) -> int
{
    spdlog::set_default_logger(spdlog::stdout_color_mt(PROJECT_NAME));
    spdlog::set_pattern(LOGGER_PATTERN);
    spdlog::enable_backtrace(BACKTRACE_SIZE);
    spdlog::set_level(spdlog::level::info);

    // clang-format off
    cxxopts::Options options(PROJECT_NAME, PROJECT_DESC);
    options.add_options()
        ("v,verbose", "Enable verbose logging")
        ("h,help", "Print program usage")
        ("input", "List of files to unpack", cxxopts::value<std::vector<std::filesystem::path>>());
    options.parse_positional({"input"});
    const auto result = options.parse(argc, argv);
    // clang-format on

    if (result["verbose"].count()) {
        spdlog::set_level(spdlog::level::trace);
        spdlog::disable_backtrace();
    }

    if (result["help"].count()) {
        spdlog::info(options.help());
        return 0;
    }

    if (result["input"].count() <= 0) {
        spdlog::info(options.help());
        return 0;
    }

    const auto input_files = result["input"].as<std::vector<std::filesystem::path>>();

    const spdlog::stopwatch watch;
    for (const auto &file : input_files) {
        if (!std::filesystem::is_regular_file(file)) {
            spdlog::warn("Found a non-regular file: ({})", file.string());
            continue;
        }

        auto out = file.parent_path() / (file.stem().string() + "_unpacked");
        if (!std::filesystem::exists(out)) {
            std::filesystem::create_directories(out);
        } else {
            spdlog::warn("Found already unpacked files: ({})", out.string());
            continue;
        }

        spdlog::info("Unpacking {}", out.string());
        const auto res = ceu::unpack(file, out);
        if (res != ceu::OK) {
            spdlog::error("Failed to extract file with error {}",
                ceu::unpackResultString[res]);
            spdlog::dump_backtrace();
        }
    }
    spdlog::info("Unpacking took {}ms", watch.elapsed_ms().count());

    spdlog::info("Finished! Thanks for using me!");
    return 0;
}
