project(core)

add_library(Core STATIC src/Core.cpp)

target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(Core)

add_library(Engine ALIAS Core)
