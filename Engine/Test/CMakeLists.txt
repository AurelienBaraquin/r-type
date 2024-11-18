cmake_minimum_required(VERSION 3.10)
project(Test)

# Activer le support des tests
enable_testing()

# Ajouter l'exécutable pour les tests
add_executable(${PROJECT_NAME}
    src/Test.cpp
    src/Serialization.cpp
)

# Options de couverture
option(COVERAGE "Enable coverage reporting" ON)

if(COVERAGE AND (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
    message(STATUS "Coverage enabled")
    target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage --coverage)
    target_link_options(${PROJECT_NAME} PRIVATE --coverage)
endif()

# Inclure les headers
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Lier avec les bibliothèques nécessaires
target_link_libraries(${PROJECT_NAME} PRIVATE
    Engine
    gtest::gtest
)

# Ajouter le test à la suite de test CTest
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
