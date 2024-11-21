speed = 5
local test = 10
function update(e)
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

    if (e == 1) then
        test = test + 1
    end

    setPosition(e, position)

    print(test)
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