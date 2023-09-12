cmake_minimum_required(VERSION 3.1.2)

project("C++ Heap Implementation")

set(LIBRARY_NAME "heap")
set(HEAP_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CATCH2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/Catch2)

add_library(${LIBRARY_NAME} INTERFACE) 
target_include_directories(${LIBRARY_NAME} INTERFACE include/) 

add_subdirectory(${CATCH2_DIR})
add_subdirectory(tests)