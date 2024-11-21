cmake_minimum_required(VERSION 3.23)
project(RType-Project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

find_package(GTest REQUIRED)
find_package(lua REQUIRED)
find_package(sol2 REQUIRED)
find_package(Chipmunk2D)
find_package(SDL2_image)
find_package(SDL2)
find_package(nlohmann_json)

add_subdirectory(Engine)
add_subdirectory(Games)
