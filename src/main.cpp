#include "main.hpp"

#include "unpack.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"

#include "cxxopts.hpp"

int main(const int argc, const char **argv)
{
    spdlog::set_default_logger(spdlog::stdout_color_mt(PROJECT_NAME));
    spdlog::set_pattern(LOGGER_PATTERN);
    spdlog::enable_backtrace(5);
    spdlog::set_level(spdlog::level::info);

    // clang-format off
    cxxopts::Options options(PROJECT_NAME, PROJECT_DESC);
    options.add_options()
        ("v,verbose", "Enable verbose logging")
        ("h,help", "Print program usage");
    options.parse_positional({"input"});
    const auto result = options.parse(argc, argv);
    // clang-format on

    if (result["verbose"].as<bool>()) {
        spdlog::set_level(spdlog::level::trace);
        spdlog::disable_backtrace();
    }

    if (result["help"].as<bool>()) {
        spdlog::info(options.help());
        return 0;
    }

    if (result.count("input") <= 0) {
        spdlog::info(options.help());
        return 1;
    }

    const auto inputFiles = result["input"].as<std::vector<std::filesystem::path>>();

    const spdlog::stopwatch sw;
    for (auto file : inputFiles) {
        if (!std::filesystem::is_regular_file(file)) {
            spdlog::warn("Found a non-regular file: ({})", file.string());
            continue;
        }

        auto out = file.parent_path() / (file.filename().string() + "_unpacked");
        if (!std::filesystem::exists(out)) {
            std::filesystem::create_directories(out);
        } else {
            spdlog::info("Found already unpacked files: {}", out.string());
            continue;
        }

        const auto res = ceu::unpack(file);
        if (res != ceu::OK) {
            spdlog::warn("Failed to extract file with error {}",
                ceu::unpackResultString[res]);
            spdlog::dump_backtrace();
        }
    }
    spdlog::info("Unpacking took {}ms", sw.elapsed_ms().count());

    spdlog::info("Finished! Thanks for using me!");
    return 0;
}
