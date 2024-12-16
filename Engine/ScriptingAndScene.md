# Luas Scripting function documentation

# Summary

- [Introduction](#introduction)
- [Scene](#scene)
- [Components](#Components)

# Introduction

This document describes the scripting functions available in the engine.

# Scene
Scene is where are stocked entities, it's define entities components, sprite, position etc

```json
{
  "sceneTag": "MainScene",
  "entities": [
    {
      "_name_": "Player",
      "tags" : ["player"],
      "components": {
        "Position": { "x": 400, "y": 200, "z": 0 },
        "Scale": { "x": 1, "y": 1 },
        "Rotation": { "angle": 0 },
        "Sprite": { "spriteID": 0 },
        "Area2D": { "width": 32, "height": 32 },
        "Script": { "scriptPath": "Games/RType/script/left.lua" }
      }
    },
    {
      "_name_": "Enemy",
      "tags" : ["enemy"],
      "components": {
        "Position": { "x": 100, "y": 200, "z": 0 },
        "Scale": { "x": 1, "y": 1 },
        "Rotation": { "angle": 0 },
        "Sprite": { "spriteID": 0 },
        "Area2D": { "width": 32, "height": 32 },
        "Input": { "inputConfigID": 0 },
        
        "Animation": { "animationID": 0, "currentFrame": 0, "frameTime": 2.0, "elapsedTime": 0.0, "loop": true, "playing": true },
        "Script": { "scriptPath": "Games/RType/script/right.lua" }
      }
    }
  ],
  "scenes" : [
    "assets.json"
  ]
}
```

# Scripts
it's recommended that all scripts should have the following structure:
```lua
self = nil
function init(e) -- initalize once 
    self = e
end

function update(dt) -- update every frame
    -- do something
end
```
# Components

## Transform components

### Position
```lua
-- Get position
local pos = getPosition(entityId)
print(pos.x, pos.y, pos.z)

-- Set position
setPosition(entityId, {
x = 100,
y = 200,
z = 0
})
```

### Rotation
```lua
-- Get rotation
local angle = getRotation(entityId)
print(angle)

-- Set rotation
setRotation(entityId, {
angle = 0
})
```

### Scale
```lua
-- Get scale
local scale = getScale(entityId)
print(scale.x, scale.y)

-- Set scale
setScale(entityId, {
x = 1,
y = 1
})
```

## Script components

### method call and check
```lua
-- Call method
callMethod(entityId, "methodName", arg1, arg2)

-- Has method
hasMethod(entityId, "methodName")
```

## Collisions components

### Area2D
area2D is a component that handles when 2 entities intersect.
```lua
-- onCollide
function onCollide(e) -- e is the other
    -- do something
end

function onEndCollide(e)
    -- do something
end

```

## Tags 
tags handle the entity tags
```lua
-- Add tag
addTag(entityId, "tag")

--has tag
hasTag(entityId, "tag")

-- remove tag
removeTag(entityId, "tag")
```
