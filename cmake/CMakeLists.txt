cmake_minimum_required(VERSION 3.25)

include_guard()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER             "/usr/bin/clang++")
set(ENABLE_FAST_MATH ON)
set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra")
SET (CMAKE_C_COMPILER   "/usr/bin/clang")
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/6910c9d9165801d8827d628cb72eb7ea9dd538c5.zip
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG       6910c9d9165801d8827d628cb72eb7ea9dd538c5 # release-1.16.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

project(mlone VERSION 1.0
    DESCRIPTION "simple cpu based neural network"
    LANGUAGES CXX)

set(ROOT_SRC_DIR "../app")
file(GLOB SOURCES "${ROOT_SRC_DIR}/src/*.cpp")
file(GLOB TESTLIB "${ROOT_SRC_DIR}/testing/*.cc")
file(GLOB TESTSRC "${ROOT_SRC_DIR}/src/*.cpp")
list(FILTER TESTSRC EXCLUDE REGEX "src/main.cpp")

include_directories(app/include)

add_executable(mlone.bin ${SOURCES})

enable_testing()
add_executable(test.bin ${TESTSRC} ${TESTLIB})

target_link_libraries(
   test.bin
   GTest::gtest_main
 )

include(GoogleTest)
gtest_discover_tests(test.bin)
