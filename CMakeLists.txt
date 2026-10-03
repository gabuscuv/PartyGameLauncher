cmake_minimum_required(VERSION 3.15)

project(PartyGameLauncher
    VERSION 1.0
    LANGUAGES C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_INSTALL_PREFIX
    "${CMAKE_SOURCE_DIR}/bin"
    CACHE PATH "Installation prefix" FORCE
)

# ---------------------------------------------------------
# Project
# ---------------------------------------------------------

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME}
    PRIVATE raylib
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# ---------------------------------------------------------
# raylib
# ---------------------------------------------------------

if (NOT EXISTS "${CMAKE_SOURCE_DIR}/raylib/CMakeLists.txt")
    message(FATAL_ERROR
        "raylib submodule is not initialized.\n"
        "Run:\n"
        "  git submodule update --init --recursive\n"
    )
endif()

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(
    "${CMAKE_SOURCE_DIR}/raylib"
    "${CMAKE_BINARY_DIR}/raylib"
)

# ---------------------------------------------------------
# libusb
# ---------------------------------------------------------
find_package(PkgConfig REQUIRED)
pkg_check_modules(libusb REQUIRED IMPORTED_TARGET libusb-1.0)

target_link_libraries(${PROJECT_NAME} PRIVATE
    PkgConfig::libusb
)

# ---------------------------------------------------------
# Install
# ---------------------------------------------------------

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION .
)

install(
    DIRECTORY "${CMAKE_SOURCE_DIR}/resources/"
    DESTINATION resources
)

# ---------------------------------------------------------
# macOS
# ---------------------------------------------------------

if (APPLE)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            "-framework IOKit"
            "-framework Cocoa"
            "-framework OpenGL"
    )
endif()