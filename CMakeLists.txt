# ===================================================================
# rOTworm - CMake Build System
# Version: 0.1.0
# ===================================================================

cmake_minimum_required(VERSION 3.16)

# --- 1. Project Definition ---
# Define the project name, version, and language.
# Set the C++ standard to C++17, which is required for our modern tools.
project(rOTworm VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 2. Vcpkg & Dependencies ---
# This section tells CMake to find the vcpkg.json manifest file.
# vcpkg will automatically find and install all the dependencies listed in it.
# We then use find_package() for each one to load them into CMake.
find_package(Boost REQUIRED COMPONENTS system thread asio)
find_package(SQLite3 REQUIRED)
find_package(pugixml REQUIRED)
find_package(Lua REQUIRED)
find_package(Cryptopp REQUIRED)
find_package(LibXml2 REQUIRED)

# GMP requires using PkgConfig, as instructed by vcpkg's output.
find_package(PkgConfig REQUIRED)
pkg_check_modules(GMP_PC REQUIRED IMPORTED_TARGET gmp)

# --- 3. Source Files & Executable ---
# Find all our .cpp source files and create the final executable target.
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(rotworm ${SOURCES})

# --- 4. Target Configuration ---
# Apply settings directly to our 'rotworm' target.

# Add our own 'src' folder to the include path so we can use #include "player.h", etc.
target_include_directories(rotworm PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Link all the necessary libraries.
# Modern CMake targets (like Boost::asio) also add their own include directories
# and definitions automatically, making this section clean and powerful.
target_link_libraries(rotworm PRIVATE
    # Vcpkg-found libraries
    Boost::system
    Boost::thread
    Boost::asio
    SQLite::SQLite3
    pugixml::pugixml
    PkgConfig::GMP_PC
    ${LUA_LIBRARIES}
    ${CRYPTOPP_LIBRARIES}
    ${LIBXML2_LIBRARIES}

    # Windows-specific system library for crash dumps
    DbgHelp
)

# Add compiler definitions needed for the legacy code to work.
target_compile_definitions(rotworm PRIVATE
    # Silence warnings about older, "unsafe" C functions like strcpy.
    _CRT_SECURE_NO_WARNINGS
    # This enables the code inside the #ifdef __USE_OTPCH__ block in otpch.h.
    __USE_OTPCH__
    # This silences a deprecation warning from an older Boost.Bind usage pattern.
    BOOST_BIND_GLOBAL_PLACEHOLDERS
)

# --- End of Configuration ---