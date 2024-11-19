# Game Engine Components

This document describes the components of the game engine.

# Engine components

# Transform components

## Position

A component that handles the world position of an entity

### Properties:
 - ```x, y```: The position of the entity in the world
 - ```z```: The depth of the entity in the world, used for rendering order

### Usage:
    
```cpp
Position position;
position.x = 0;
position.y = 0;
position.z = 0;
```

## Rotation

A component that handles the rotation of an entity

### Properties:
- ```angle```: The angle of the entity in the world in float degrees

<h3>Usage: </h3>

```cpp
Rotation rotation;
rotation.angle = 0;
```

## Scale:

A component that handles the scale of an entity

### Properties:
- ```x, y```: The scale of the entity in the world

## BoxCollider

A component that handles collision detection between entities

### Properties:
 - ```x,y```: The position of the collider relative to the entity position
 - ```width, height```: The size of the collider
 - ```onCollisionEnter(Entity const& other)```: The function to call when a collision is detected

### Usage:

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


# Modules

## Adding a new module

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

## Adding it to the task builder

To add the module to the task builder, add it to the Taskfile.yml

```  build:
    desc: "Build the project with conan-release preset"
    cmds:
      - cmake --preset conan-release -DBUILD_RTYPE=ON -DBUILD_TESTS=OFF -DGRAPHIC=ON -DMYMODULE=ON```
```

## Adding it to the engine

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

## Adding it to the game

To add the module to the game, add the following line to your cmake game file:

```cmake
target_link_libraries(${PROJECT_NAME} PRIVATE
    Engine::MyModule
)
```