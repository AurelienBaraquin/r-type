project(Physics)

add_library(Physics STATIC src/Physics.cpp
                src/Boxcollider.cpp)

target_include_directories(Physics PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/components)

target_link_libraries(Physics PRIVATE Core chipmunk2d::chipmunk2d)

add_library(Engine::Physics ALIAS Physics)
