-- ENEMY SCRIPT

speed = 5
self = nil
function init(e)
    self = e
    print("init")
end

function update(delta)
    local position = getPosition(self)

    local rot = getRotation(self)
    rot.angle = rot.angle + speed / 5
    setRotation(self, rot)

    if isInputActive(self, "MoveUp") then
        position.y = position.y - speed
    end
    if isInputActive(self, "MoveDown") then
        position.y = position.y + speed
    end
    if isInputActive(self, "MoveLeft") then
        position.x = position.x - speed
    end
    if isInputActive(self, "MoveRight") then
        position.x = position.x + speed
    end
    if isInputActive(self, "Shoot") then
        x, y = getMousePosition(self, mouse_pos)
        position.x = x
        position.y = y
        playSoundEffect("Games/RType/assets/sounds/shoot.ogg", 100.0)
        playAnimation(self, 1)
    end
    setPosition(self, position)
end

function onCollide(other)
    print(other)
    destroyEntity(other)
    local position = getPosition(self)
    position.x = position.x + 1
    setPosition(self, position)
end

function setSpeed(self, newSpeed)
    if newSpeed ~= nil then
        speed = newSpeed
    end
end
