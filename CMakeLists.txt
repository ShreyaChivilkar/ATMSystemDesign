cmake_minimum_required(VERSION 3.10)
project(ATMSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Include dirs ===
include_directories(
    src
    src/states
    src/services
    src/presenter
    src/data
    src/constants)

# === Source files ===
file(GLOB_RECURSE  SOURCES "src/*.cpp")

# === Main app executable ===
add_executable(atm_app ${SOURCES})

# === GoogleTest & GoogleMock ===
add_subdirectory(external/googletest)
enable_testing()

# === Build a static library from main sources to reuse in tests ===
add_library(atm_lib STATIC ${SOURCES})

# === Test files ===
file(GLOB_RECURSE  TEST_SOURCES "tests/*.cpp")
# === Tests executable ===
add_executable(atm_tests ${TEST_SOURCES})

# === Link with GTest, GMock, pthread, and ATM library ===
target_link_libraries(atm_tests gtest_main gmock pthread atm_lib)

include(GoogleTest)
gtest_discover_tests(atm_tests)
