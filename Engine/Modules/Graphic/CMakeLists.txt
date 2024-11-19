project(Graphic)

add_library(Graphic STATIC src/Graphic.cpp
    src/Texture.cpp
    src/AnimationManager.cpp
    src/SpriteManager.cpp
    src/TextureManager.cpp)

target_include_directories(Graphic PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/components)

target_link_libraries(Graphic PRIVATE Core SDL2_image::SDL2_image SDL2::SDL2main)

add_library(Engine::Graphic ALIAS Graphic)
