project(core)

add_library(Core STATIC src/Core.cpp
    src/EntityManager.cpp
    src/Registry.cpp
    src/ScriptBindings.cpp
    src/ScriptSystem.cpp
    src/ComponentFactory.cpp
    src/Event.cpp
    src/Scene.cpp)

target_link_libraries(Core PRIVATE sol2::sol2 lua::lua nlohmann_json::nlohmann_json)

target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/components
    ${CMAKE_CURRENT_SOURCE_DIR}/include/entity
    ${lua_INCLUDE_DIRS}
    ${sol2_INCLUDE_DIRS}
    ${nlohmann_json_INCLUDE_DIRS})

add_library(Engine ALIAS Core)
