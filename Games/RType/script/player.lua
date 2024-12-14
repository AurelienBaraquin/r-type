speed = 5
self = nil
shoot_timer = 0
shoot_rate = 5


function init(e)
    self = e
    print("init as " .. e)
end

function update(delta)
    local position = getPosition(self)

    local rot = getRotation(self)
    rot.angle = rot.angle + speed / 5
    if type(position) ~= "table" then
        print("position is not a table")
        return
    end
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
    if isInputActive(self, "Shoot", false) and shoot_timer <= 0 then
        shoot_timer = shoot_rate
        playAnimation(self, 1)
        local bullet_position = {
            x = position.x + 10,
            y = position.y - 20,
            z = position.z
        }
        bullet = createEntity("Bullet")
        setPosition(bullet, bullet_position)
        playSoundEffect("Games/RType/assets/sounds/shoot.ogg", 100.0)
    end
    if shoot_timer > 0 then
        shoot_timer = shoot_timer - 1
    end
    setPosition(self, position)
end

function onCollide(other)
end

function setSpeed(self, newSpeed)
    if newSpeed ~= nil then
        speed = newSpeed
    end
end
