project(Audio)

add_library(Audio STATIC
    src/Audio.cpp
    src/ComponentFactory.cpp
    src/ScriptBindings.cpp
)

target_include_directories(Audio PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SFML_INCLUDE_DIR}
)

target_link_libraries(Audio PUBLIC
    Core
    raylib
)

add_library(Engine::Audio ALIAS Audio)
