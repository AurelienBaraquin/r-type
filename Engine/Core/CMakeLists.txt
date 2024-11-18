project(core)

add_library(Core STATIC src/Core.cpp
    src/EntityManager.cpp
    src/Registry.cpp)

target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/components)

target_link_libraries(Core PRIVATE)

add_library(Engine ALIAS Core)
