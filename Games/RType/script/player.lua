speed = 3
self = nil
shoot_timer = 0
shoot_rate = 10
hp = 1000
can_move = true

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
    position = handle_move(position)
    if isInputActive(self, "Reload", true) then
        reloadScene("Games/RType/config/scene.json")
    end
    if isInputActive(self, "Shoot", true) and shoot_timer <= 0 then
        shoot_timer = shoot_rate
        playAnimation(self, 1)
        local bullet_position = {
            x = position.x + 10,
            y = position.y - 20,
            z = position.z
        }
        bullet = createEntity("Bullet")
        addTag(bullet, "MainScene")
        setPosition(bullet, bullet_position)
        playSoundEffect("Games/RType/assets/sounds/shoot.ogg", 20.0)
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

function handle_move(position)
    if can_move == false then
        return position
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
    return position
end

function damage(dmg)
    hp = hp - dmg
    if self ~= nil and hp < 0 then
        reloadScene("Games/RType/config/scene.json")
    end
end
