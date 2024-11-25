speed = 5
function update(delta)
    local position = getPosition(e)

    local rot = getRotation(e)
    rot.angle = rot.angle + speed/5
    setRotation(e, rot)

    if isInputActive(e, "MoveUp") then
        position.y = position.y - speed
    end
    if isInputActive(e, "MoveDown") then
        position.y = position.y + speed
    end
    if isInputActive(e, "MoveLeft") then
        position.x = position.x - speed
    end
    if isInputActive(e, "MoveRight") then
        position.x = position.x + speed
    end
    if isInputActive(e, "Shoot") then
        position.y = 10
    end

    setPosition(e, position)
end

function onCollide(other)
    local position = getPosition(e)
    position.x = position.x + 1
    setPosition(e, position)
end

function setSpeed(e, newSpeed)
    if newSpeed ~= nil then
        speed = newSpeed
    end
end