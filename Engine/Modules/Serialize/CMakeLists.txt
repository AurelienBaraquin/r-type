project(Serialize)


add_library(Serialize STATIC src/Serialize.cpp)

target_include_directories(Serialize PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/components
        ${chipmunk2d_INCLUDE_DIRS})

target_link_libraries(Serialize PRIVATE Core chipmunk2d::chipmunk2d SDL2::SDL2main)

add_library(Engine::Serialize ALIAS Serialize)
