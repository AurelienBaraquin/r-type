# Luas Scripting function documentation

# Summary

- [Introduction](#introduction)



# Introduction

This document describes the scripting functions available in the engine.


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



