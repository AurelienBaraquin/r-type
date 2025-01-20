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


The game engine project is a C++ project that aims to create a game engine.
The engine is based on the [ECS (Entity Component System)](https://en.wikipedia.org/wiki/Entity_component_system) architecture.
This project is aimed for game developers who want to create a game using a custom engine.
It was created for a school project at EPITECH.


<br><br>


## Components

### Graphic components

Graphic components handle the visual representation of entities in the game world. Examples include:
- **Sprite**: Holds texture information.
- **Transform**: Contains position, scale, and rotation.

### Physics Components

Physics components define the physical properties and behaviors of entities, such as:
- **Position**: Tracks the location of an entity.
- **Scale**: Represents the size of an entity.
- **Velocity**: Specifies movement speed and direction.

### Adding New Components

To add a new component:
1. Create a new header file under `Engine/Core/include/components/`.
2. Define the component structure.
   ```cpp
   #pragma once
   struct NewComponent {
       int data;
   };
   ```


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

```python
from conan import ConanFile
from conan.tools.cmake import cmake_layout

class CactusEngine(ConanFile):
    name = "CactusEngine"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = ["CMakeDeps", "CMakeToolchain"]
    default_options = {"*:shared": False}

    def requirements(self):
        self.requires("gtest/1.15.0")
        self.requires("raylib/5.5")
        self.requires("sol2/3.3.1")
        self.requires("lua/5.4.6")
        self.requires("chipmunk2d/7.0.3")
        self.requires("cista/0.15")
        self.requires("nlohmann_json/3.11.3")
        self.requires("flac/1.4.3", force=True)
        self.requires("asio/1.32.0")
        self.requires("cereal/1.3.2")
        # Others...

    def layout(self):
        self.folders.build = "build/Release"
        self.folders.generators = "build/Release/generators"
        self.folders.source = "src"
        cmake_layout(self)

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
find_package(Raylib)
find_package(nlohmann_json)

add_subdirectory(Engine)
add_subdirectory(Games)

```

# Adding New Functions for Lua Scripting

This section explains how to add new C++ functions to the Lua scripting system in the game engine.

## Step 1: Define the Function in C++

Create the C++ function you want to expose to Lua. For example:

```cpp
#include <iostream>
#include <string>

void printMessage(const std::string& message) {
    std::cout << "Lua says: " << message << std::endl;
}
```

This function takes a string as input and prints it to the console.

## Step 2: Bind the Function in ScriptBindings.cpp

Open the ScriptBindings.cpp file and register the function using the Lua binding library (e.g., Sol2):

```cpp
#include <sol/sol.hpp>
#include "ScriptBindings.hpp"

void ScriptBindings::bindFunctions(sol::state& lua) {
    lua.set_function("printMessage", &printMessage);
}
```

Here, the printMessage function is bound to Lua with the name printMessage.

## Step 3: Call the Function in a Lua Script

In your Lua script, you can now call the function as if it were natively available:

```lua
printMessage("Hello from Lua!")
```

When the Lua script runs, it will call the C++ function and print the message to the console.
