cmake_minimum_required(VERSION 3.26)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(InternshipTasks)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

add_subdirectory(Task1)
add_subdirectory(Task1/Tests)
add_subdirectory(Task2)
add_subdirectory(Task2/Tests)
add_subdirectory(Task3)
add_subdirectory(Task3/Tests)
