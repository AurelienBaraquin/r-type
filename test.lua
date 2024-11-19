function update()
    local position = getPosition()
    local rotation = getRotation()
    rotation.angle = rotation.angle + 5
    position.x = position.x + 2
    position.y = position.y + 2
    setPosition({x = position.x, y = position.y, z = position.z})
    setRotation({angle = rotation.angle})
end
