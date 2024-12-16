project(Graphic)

add_library(Graphic STATIC src/Graphic.cpp
    src/AnimationSystem.cpp
    src/SpriteSystem.cpp
    src/TextureSystem.cpp
    src/ScriptBindings.cpp
    src/ComponentFactory.cpp)

target_include_directories(Graphic PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/components)

target_link_libraries(Graphic PUBLIC Core raylib)

add_library(Engine::Graphic ALIAS Graphic)
