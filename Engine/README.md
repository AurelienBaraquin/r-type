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


# Graphics 