cmake_minimum_required(VERSION 3.25)
include_guard()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_COMPILER             "/usr/bin/clang++")
set(ENABLE_FAST_MATH ON)
# set(CMAKE_BUILD_TYPE Debug)
 set(CMAKE_CXX_FLAGS "-O2")
SET (CMAKE_C_COMPILER             "/usr/bin/clang")
SET (CMAKE_AR      "/usr/bin/llvm-ar")
SET (CMAKE_LINKER  "/usr/bin/llvm-ld")
SET (CMAKE_NM      "/usr/bin/llvm-nm")
SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib")
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e4fdb87e76b9fc4b01c54ad81aea19d6e994b994.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

project(mlone VERSION 1.1
    DESCRIPTION "simple cpu based neural network"
    LANGUAGES CXX)
file(GLOB SOURCES "src/*.cpp")
file(GLOB TESTSRC "src/**/*.cc")
file(GLOB TESTSRCCPP "src/*.cpp")
list(FILTER TESTSRCCPP EXCLUDE REGEX "src/main.cpp")
include_directories(src/include)
add_executable(mlone.exe ${SOURCES})
# enable_testing() 
# add_executable(test.exe ${TESTSRC} ${TESTSRCCPP})
#
# target_link_libraries(
#   test.exe
#   GTest::gtest_main
# )
#
# include(GoogleTest)
# gtest_discover_tests(test.exe)
