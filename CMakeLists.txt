cmake_minimum_required(VERSION 3.10)
project(libglenda C ASM)

# Options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Architecture selection (default to riscv64)
if(NOT DEFINED ARCH)
    set(ARCH "riscv64")
endif()

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/ipc/ipc.c
    src/cap/cap.c
    src/sys.c
    src/console.c
    src/utils.c
    src/stdio.c
    src/crt0.c
)

# Architecture specific sources
if(ARCH STREQUAL "riscv64")
    list(APPEND SOURCES src/arch/riscv64/crt0.S)
elseif(ARCH STREQUAL "x86_64")
    list(APPEND SOURCES src/arch/x86_64/crt0.S)
else()
    message(FATAL_ERROR "Unsupported architecture: ${ARCH}")
endif()

# Create static library
add_library(glenda STATIC ${SOURCES})

# Compiler flags
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(glenda PRIVATE
        -Wall -Wextra -Wno-unused-parameter
        -fno-builtin -ffreestanding
    )
endif()

# Install rules
install(TARGETS glenda
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/glenda
    DESTINATION include
)
