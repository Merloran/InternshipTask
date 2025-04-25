cmake_minimum_required(VERSION 3.26)

set(targetName CollisionTest)
project(${targetName})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest CONFIG REQUIRED)

add_executable(${targetName} "main.cpp")

if(MSVC)
    target_compile_options(${targetName} PRIVATE /utf-8)
endif()

target_include_directories(${targetName} PRIVATE ${TASK2_INCLUDE_DIR})

target_link_libraries(${targetName} PRIVATE
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
    ${TASK2_LIB}
)

add_test(NAME ${targetName} COMMAND ${targetName})