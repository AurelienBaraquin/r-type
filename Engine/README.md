# Game engine project documentaiton

# Summary

- [Game engine project documentaiton](#game-engine-project-documentaiton)
- [Summary](#summary)
- [Introduction](#introduction)
  - [About](#about)
- [Components](#components)
- [Graphic components](#graphic-components)
- [Physics components](#physics-components)
- [ADD new components](#add-new-components)
- [Modules](#modules)
  - [Adding a new module](#adding-a-new-module)
    - [Step 1: Create the module](#step-1-create-the-module)
    - [Step 2: Adding it to the task builder](#step-2-adding-it-to-the-task-builder)
    - [Step 3: Adding it to the engine](#step-3-adding-it-to-the-engine)
    - [Step 4: Add the module to the game](#step-4-add-the-module-to-the-game)
    - [Step 5: add it to the taskfile.yml](#step-5-add-it-to-the-taskfileyml)
- [Adding a library to the engine](#adding-a-library-to-the-engine)
- [Adding new functions for lua scripting](#adding-new-functions-for-lua-scripting)


# Introduction

This document describes the architecture of the game engine project,
the components, and the modules.

## About

The game engine project is a C++ project that aims to create a game engine.
The engine is based on the [ECS (Entity Component System)](https://en.wikipedia.org/wiki/Entity_component_system) architecture.
This project is aimed for game developers who want to create a game using a custom engine.
It was created for a school project at EPITECH.


<br><br>


# Components

This document describes the components.

# Graphic components

TODO: Add graphic components

# Physics components

TODO: Add physics components

# ADD new components



# Modules

## Adding a new module

### Step 1: Create the module

To add a new module, create a new folder in the ```Engine/Modules``` directory. The folder should contain the following files:

- ```CMakeLists.txt```: The CMake file for the module
- ```ìnclude``` and ```src``` directories should be added to the module

here is an example of CMakelists.txt file for a module:

```cmake
project(MyModule)

add_library(Graphic STATIC src/file.cpp
    src/file2.cpp
    src/file3.cpp)

target_include_directories(MyModule PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/components)

target_link_libraries(MyModule PRIVATE Core SDL2_image::SDL2_image SDL2::SDL2main)

add_library(Engine::MyModule ALIAS MyModule)
```

### Step 2: Adding it to the task builder

To add the module to the task builder, add it to the Taskfile.yml

```  build:
    desc: "Build the project with conan-release preset"
    cmds:
      - cmake --preset conan-release -DBUILD_RTYPE=ON -DBUILD_TESTS=OFF -DGRAPHIC=ON -DMYMODULE=ON```
```

### Step 3: Adding it to the engine

To add the module to the engine, add the following line to the ```Engine/CMakeLists.txt``` file:

```cmake
project(Engine)

add_subdirectory(Core)

if(BUILD_TESTS)
    add_subdirectory(Test)
endif()

if(GRAPHIC)
    add_subdirectory(Modules/Graphic)
endif ()

if (PHYSICS)
    add_subdirectory(Modules/Physics)
endif()
```

### Step 4: Add the module to the game

To add the module to the game, add the following line to your cmake game file:

```cmake
target_link_libraries(${PROJECT_NAME} PRIVATE
    Engine::MyModule
)
```

### Step 5: add it to the taskfile.yml
```
      - cmake --preset conan-release -DBUILD_RTYPE=ON -DBUILD_TESTS=OFF -DBUILD_TOOLS=ON -DGRAPHIC=ON -DPHYSICS=ON -DINPUTS=ON
```

# Adding a library to the engine

To add a library to the engine, first add it to the conanfile.txt then add it to the CMakeList.txt

```txt
[requires]
gtest/1.15.0
incbin/cci.20211107
sdl/2.28.3
sdl_image/2.6.3
sol2/3.3.1
lua/5.4.6
chipmunk2d/7.0.3 <----- add here
```

```cmake
cmake_minimum_required(VERSION 3.23)
project(RType-Project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

find_package(GTest REQUIRED)
find_package(incbin REQUIRED)
find_package(lua REQUIRED)
find_package(sol2 REQUIRED)
find_package(Chipmunk2D) <----- add here
find_package(SDL2_image)
find_package(SDL2)
find_package(nlohmann_json)

add_subdirectory(Engine)
add_subdirectory(Games)

```

# Adding new functions for lua scripting

To add new functions for lua scripting, add the following code to the ```ScriptBindings.cpp``` file:

```cpp