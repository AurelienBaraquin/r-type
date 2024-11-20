# Game engine project documentaiton

# Summary

- [Introduction](#introduction)
- [Components](#components)
    - [Engine components](#engine-components)
    - [Graphic components](#graphic-components)
    - [Physics components](#physics-components)
    - [Audio components](#audio-components)
    - [Input components](#input-components)
    - [Network components](#network-components)
    - [add new components](#add-new-components)
- [Modules](#modules)
  - [Adding a new module](#adding-a-new-module)
- [Adding a library to the engine](#adding-a-library-to-the-engine)


# Introduction

This document describes the architecture of the game engine project,
the components, and the modules.

## About

The game engine project is a C++ project that aims to create a game engine.
The engine is based on the [ECS (Entity Component System)](https://en.wikipedia.org/wiki/Entity_component_system) architecture.
This project is aimed for game developers who want to create a game using a custom engine.
It was created for a school project at EPITECH.


## Demo
TODO: Add demo

## Tech Stack
TODO: Add tech stack

- C++
- CMake
- Conan

### Graphics:

- SDL2

### Scripting:
- Sol2

## Prerequisites
 TODO: Add prerequisites

- Task (Task runner)
- CMake
- Conan

## Installation
TODO: Add installation instructions

```bash
git clone https://github.com/EpitechPromo2027/B-CPP-500-MPL-5-2-rtype-guillaume1.tran.git
cd B-CPP-500-MPL-5-2-rtype-guillaume1.tran
task i
task b
task rtype
```

The engine is based on the [ECS (Entity Component System)](https://en.wikipedia.org/wiki/Entity_component_system) architecture.
The engine is composed of components and modules.

<br><br>


# Components

This document describes the components.

# Engine components

### Transform components

### Position

A component that handles the world position of an entity

#### Properties:
 - ```x, y```: The position of the entity in the world
 - ```z```: The depth of the entity in the world, used for rendering order

#### Usage:
    
```cpp
Position position;
position.x = 0;
position.y = 0;
position.z = 0;
```

### Rotation

A component that handles the rotation of an entity

#### Properties:
- ```angle```: The angle of the entity in the world in float degrees

<h3>Usage: </h3>

```cpp
Rotation rotation;
rotation.angle = 0;
```

### Scale:

A component that handles the scale of an entity

#### Properties:
- ```x, y```: The scale of the entity in the world

#### Usage:

```cpp
void test(Entity const& other) {
    std::cout << "Collision detected with other box " << std::endl;
}

BoxCollider collider;
collider.x = 0;
collider.y = 0;
collider.width = 10;
collider.height = 10;
collider.onCollisionEnter = test;
```

Current issue: The collision detection is useless, as the BoxCollider doesn't have a reference to the entity it is attached to.

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