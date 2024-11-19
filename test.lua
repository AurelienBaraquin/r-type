function update(e)
    local position = getPosition(e)
    local rotation = getRotation(e)
    rotation.angle = rotation.angle + 5
    position.x = position.x + 2
    position.y = position.y + 2
    setPosition(e, {x = position.x, y = position.y, z = position.z})
    setRotation(e, {angle = rotation.angle})
end
