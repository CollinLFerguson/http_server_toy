cmake_minimum_required(VERSION 3.20)
project(http_server LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # gives you compile_commands.json for tooling

# --- Source discovery ---
# GLOB_RECURSE is the direct equivalent of your `find` call, but it has a
# known gotcha: CMake won't notice new files added later without re-running
# cmake. For a project this size, explicitly listing sources is usually
# preferred long-term. Globbing is fine to get started, though:
file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/*.s"
)

add_executable(http_server ${SRCS})

# --- Include directories ---
# Instead of manually finding every subdirectory under src/ like the Makefile
# does, just point at the top of src/ and use it as the include root
# (assuming your #includes are like "moduleA/foo.h"). If you truly need
# every subdirectory on the include path individually, see the note below.
target_include_directories(http_server PRIVATE ${CMAKE_SOURCE_DIR}/src)

# --- Compiler flags ---
target_compile_options(http_server PRIVATE -Wall -Wextra -Wpedantic)

# --- clang-tidy integration (replaces `make tidy`) ---
# Option A: run automatically as part of the build
# set(CMAKE_CXX_CLANG_TIDY clang-tidy)
#
# Option B: keep it as an explicit, separate step (closer to your Makefile)
find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
    add_custom_target(tidy
        COMMAND ${CLANG_TIDY_EXE} ${SRCS} -p ${CMAKE_BINARY_DIR}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running clang-tidy"
    )
endif()