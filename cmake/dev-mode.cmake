include(cmake/folders.cmake)

#include(CTest)
#if(BUILD_TESTING)
#  add_subdirectory(test)
#endif()

add_custom_target(
    run-exe
    COMMAND CEUnpack_exe
    VERBATIM
)
add_dependencies(run-exe CEUnpack_exe)

include(cmake/lint-targets.cmake)
include(cmake/spell-targets.cmake)

add_folders(Project)
