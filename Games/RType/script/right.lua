function update(e)
    local position = getPosition(e)
    position.x = position.x + 1
    setPosition(e, position)

    local rot = getRotation(e)
    rot.angle = rot.angle + 1
    setRotation(e, rot)
end

function onCollide(e)
    local position = getPosition(e)
    position.x = position.x + 1
    setPosition(e, position)
end