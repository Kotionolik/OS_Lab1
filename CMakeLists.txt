cmake_minimum_required(VERSION 3.10)
project(OS_Lab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR})
add_definitions(-UUNICODE -U_UNICODE)

add_executable(Creator Creator.cpp)
add_executable(Main main.cpp)
add_executable(Reporter Reporter.cpp)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests test_main.cpp test_creator.cpp test_reporter.cpp)
target_link_libraries(tests gtest_main)

add_dependencies(tests Creator Reporter)

add_test(NAME tests COMMAND tests)


