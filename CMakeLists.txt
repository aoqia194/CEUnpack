cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    CEUnpack
    VERSION 0.1.0
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare executable ----

add_executable(CEUnpack_exe
        src/main.cpp
        src/main.hpp
        src/unpack.cpp
        src/unpack.hpp
        src/util.hpp
        src/types/csb.cpp
        src/types/csb.hpp
        src/types/rpack.cpp
        src/types/rpack.hpp)
add_executable(CEUnpack::exe ALIAS CEUnpack_exe)

set_property(TARGET CEUnpack_exe PROPERTY OUTPUT_NAME CEUnpack)

target_compile_features(CEUnpack_exe PRIVATE cxx_std_23)

# ---- Add dependencies ----

include(cmake/CPM.cmake)

CPMAddPackage("gh:TheLartians/Ccache.cmake@1.2.5")

set(SPDLOG_BUILD_EXAMPLE OFF)
CPMAddPackage("gh:gabime/spdlog@1.15.3")

CPMAddPackage("gh:jarro2783/cxxopts@3.3.1")

target_link_Libraries(CEUnpack_exe PRIVATE spdlog::spdlog cxxopts::cxxopts)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT CEUnpack_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of CEUnpack"
  )
endif()

include(cmake/dev-mode.cmake)
