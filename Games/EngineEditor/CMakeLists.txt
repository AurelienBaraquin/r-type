cmake_minimum_required(VERSION 3.27)
project(EngineEditor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(EngineEditor
        src/main.cpp
        include/main.hpp
        include/raygui.h
        include/Editor.hpp
        include/SceneManager.hpp
        src/Editor.cpp
        src/SceneManager.cpp
)

target_include_directories(EngineEditor PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/include
)

target_link_libraries(EngineEditor PRIVATE
        Engine
        Engine::Physics
        Engine::Graphic
        Engine::Inputs
        Engine::Audio
        raylib
)