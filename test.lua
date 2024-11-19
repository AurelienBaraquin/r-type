function update()
    local position = getPosition()
    position.x = position.x + 1
    position.y = position.y + 1
    setPosition({x = position.x, y = position.y, z = position.z})
end
