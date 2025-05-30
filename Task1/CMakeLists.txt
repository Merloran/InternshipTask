cmake_minimum_required(VERSION 3.26)

set(targetName Browser)
project(${targetName})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE HEADER_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/Code/*.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/Code/*.hpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/Code/*.inl")
	 
set(TASK1_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Code" CACHE INTERNAL "")

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

target_include_directories(${targetName} PRIVATE
						   ${CMAKE_CURRENT_SOURCE_DIR}/Code)