cmake_minimum_required(VERSION 3.12)

set(TESTS_BINARY_NAME heap_tests)
set(TEST_SOURCES test_heap.cpp)

add_executable(${TESTS_BINARY_NAME} ${TEST_SOURCES})
target_link_libraries(${TESTS_BINARY_NAME} PRIVATE Catch2::Catch2WithMain)
target_include_directories(
    ${TESTS_BINARY_NAME} PRIVATE 
    ${HEAP_INCLUDE_PATH})

target_compile_features(${TESTS_BINARY_NAME} PRIVATE cxx_std_17)