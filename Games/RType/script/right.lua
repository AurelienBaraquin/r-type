speed = 1
function update(e)
    local position = getPosition(e)
    position.x = position.x + speed
    setPosition(e, position)

    local rot = getRotation(e)
    rot.angle = rot.angle + speed/5
    setRotation(e, rot)
end

function onCollide(e)
    local position = getPosition(e)
    position.x = position.x + 1
    setPosition(e, position)
end

function setSpeed(e, newSpeed)
    print(newSpeed)
    if newSpeed ~= nil then
        speed = newSpeed
    end
end