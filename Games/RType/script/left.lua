function update(e)
    local position = getPosition(e)
    position.x = position.x - 1
    setPosition(e, position)
end
