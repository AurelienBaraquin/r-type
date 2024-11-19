project(core)

add_library(Core STATIC src/Core.cpp
    src/EntityManager.cpp
    src/Registry.cpp
    src/ScriptBindings.cpp
    src/Event.cpp)

target_link_libraries(Core PRIVATE incbin::incbin sol2::sol2 lua::lua)

target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/components
    ${CMAKE_CURRENT_SOURCE_DIR}/include/entity
    ${incbin_INCLUDE_DIRS}
    ${lua_INCLUDE_DIRS}
    ${sol2_INCLUDE_DIRS})

add_library(Engine ALIAS Core)
