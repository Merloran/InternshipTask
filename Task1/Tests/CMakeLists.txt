cmake_minimum_required(VERSION 3.26)
project(CompressorTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest CONFIG REQUIRED)

add_executable(CompressorTest "main.cpp")

if(MSVC)
    target_compile_options(CompressorTest PRIVATE /utf-8)
endif()

target_include_directories(CompressorTest PRIVATE ${TASK1_INCLUDE_DIR})

target_link_libraries(CompressorTest PRIVATE
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
)

add_test(NAME CompressorTest COMMAND CompressorTest)