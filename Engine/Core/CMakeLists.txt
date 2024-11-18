project(core)

add_library(Core STATIC src/Core.cpp
    src/EntityManager.cpp
    src/Registry.cpp
    src/AnimationManager.cpp
    src/SpriteManager.cpp
    src/TextureManager.cpp)

target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/components)

target_link_libraries(Core PRIVATE incbin::incbin)

add_library(Engine ALIAS Core)
