speed = 5
function update(e)
    local position = getPosition(e)

    local rot = getRotation(e)
    rot.angle = rot.angle + speed/5
    setRotation(e, rot)

    if isInputActive("MoveUp") then
        position.y = position.y - speed
    end
    if isInputActive("MoveDown") then
        position.y = position.y + speed
    end
    if isInputActive("MoveLeft") then
        position.x = position.x - speed
    end
    if isInputActive("MoveRight") then
        position.x = position.x + speed
    end
    if isInputActive("Shoot") then
        position.y = 10
    end

    setPosition(e, position)
end

function onCollide(e)
    local position = getPosition(e)
    position.x = position.x + 1
    setPosition(e, position)
end

function setSpeed(e, newSpeed)
    if newSpeed ~= nil then
        speed = newSpeed
    end
end