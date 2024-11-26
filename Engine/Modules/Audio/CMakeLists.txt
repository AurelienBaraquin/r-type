project(Audio)

add_library(Audio STATIC
    src/Audio.cpp
    src/AudioSystem.cpp
    src/ComponentFactory.cpp
    src/ScriptBindings.cpp
)

target_include_directories(Audio PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SFML_INCLUDE_DIR}
)

target_link_libraries(Audio PUBLIC
    Core
    sfml-audio
)

add_library(Engine::Audio ALIAS Audio)

find_package(SFML 2.5 REQUIRED COMPONENTS audio)
