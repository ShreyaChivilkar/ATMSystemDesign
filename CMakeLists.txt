cmake_minimum_required(VERSION 3.10)
project(ATMSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Include dirs ===
include_directories(src)

# === Source files ===
file(GLOB SOURCES "src/*.cpp")
file(GLOB TEST_SOURCES "tests/*.cpp")

# === Main app executable ===
add_executable(atm_app ${SOURCES})

# === GoogleTest & GoogleMock ===
add_subdirectory(external/googletest)

enable_testing()

# === Build a static library from main sources to reuse in tests ===
add_library(atm_lib STATIC ${SOURCES})

# === Tests executable ===
add_executable(atm_tests ${TEST_SOURCES})

# === Link with GTest, GMock, pthread, and ATM library ===
target_link_libraries(atm_tests gtest_main gmock pthread atm_lib)

include(GoogleTest)
gtest_discover_tests(atm_tests)
