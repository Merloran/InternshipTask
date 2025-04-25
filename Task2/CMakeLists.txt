cmake_minimum_required(VERSION 3.26)

set(targetName Collision)
project(${targetName})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(VCPKG_MANIFEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

file(GLOB_RECURSE HEADER_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/Code/*.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/Code/*.hpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/Code/*.inl")
	 
set(TASK2_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Code" CACHE INTERNAL "")

file(GLOB_RECURSE LIB_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/Code/Utilities/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Code/Render/*.cpp"
)

add_library(${targetName}Lib STATIC ${LIB_SOURCES})
target_include_directories(${targetName}Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Code)

add_executable(${targetName} "Code/main.cpp")

file(GLOB_RECURSE sourceFiles
     "${CMAKE_CURRENT_SOURCE_DIR}/Code/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/Code/*.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/Code/*.hpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/Code/*.inl")

list(REMOVE_ITEM sourceFiles "${CMAKE_CURRENT_SOURCE_DIR}/Code/main.cpp")

target_sources(${targetName} PRIVATE ${sourceFiles})

source_group("Project" FILES "Code/main.cpp")
foreach(sourceFile IN ITEMS ${sourceFiles})
    get_filename_component(sourcePath "${sourceFile}" PATH)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/Code" "" groupPath "${sourcePath}")
    string(REPLACE "/" "\\" groupPath "${groupPath}")
    source_group("Project\\${groupPath}" FILES "${sourceFile}")
endforeach()

if (MSVC)
    target_compile_options(${targetName} PRIVATE /utf-8)
endif()


target_link_libraries(${targetName} PRIVATE glfw)
target_link_libraries(${targetName} PRIVATE glad::glad)

target_link_libraries(${targetName}Lib PRIVATE glfw glad::glad)

set(TASK2_LIB ${targetName}Lib CACHE INTERNAL "")
target_link_libraries(${targetName} PRIVATE ${TASK2_LIB})

target_include_directories(${targetName} PRIVATE
						   ${CMAKE_CURRENT_SOURCE_DIR}/Code)