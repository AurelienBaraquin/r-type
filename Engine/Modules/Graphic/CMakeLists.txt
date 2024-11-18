project(Graphic)

add_library(Graphic STATIC src/Graphic.cpp)

target_include_directories(Graphic PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(Graphic PRIVATE Core raylib)

add_library(Engine::Graphic ALIAS Graphic)
