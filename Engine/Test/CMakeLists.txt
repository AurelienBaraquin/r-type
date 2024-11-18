cmake_minimum_required(VERSION 3.10)
project(Test)

enable_testing()

add_executable(${PROJECT_NAME}
    src/Test.cpp
)

option(COVERAGE "Enable coverage reporting" ON)

if(COVERAGE AND (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
    message(STATUS "Coverage enabled")
    target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage --coverage)
    target_link_options(${PROJECT_NAME} PRIVATE --coverage)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Engine
    gtest::gtest
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
