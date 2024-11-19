project(Physics)

add_library(Physics STATIC src/Physics.cpp
                src/components/BoxCollider.cpp)

target_include_directories(Physics PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/components)

target_link_libraries(Physics PRIVATE Core SDL2_image::SDL2_image SDL2::SDL2main)

add_library(Engine::Physics ALIAS Physics)
