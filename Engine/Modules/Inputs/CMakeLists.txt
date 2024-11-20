project(Inputs)

add_library(Inputs STATIC src/Inputs.cpp
        src/ComponentFactory.cpp
        src/ScriptBindings.cpp
        src/InputSystem.cpp)

target_include_directories(Inputs PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/components)

target_link_libraries(Inputs PRIVATE Core nlohmann_json::nlohmann_json)

add_library(Engine::Inputs ALIAS Inputs)
