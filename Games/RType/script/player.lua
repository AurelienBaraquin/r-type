speed = 3
self = nil
shoot_timer = 0
shoot_rate = 10
hp = 10000
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
    if isInputActive(self, get_table_input()[5], true) and shoot_timer <= 0 then
        shoot_timer = shoot_rate
        playAnimation(self, 1)
        local bullet_position = {
            x = position.x + 10,
            y = position.y + 4,
            z = position.z
        }
        bullet = createEntity("Bullet")
        addTag(bullet, "MainScene")
        setPosition(bullet, bullet_position)
        callMethod(bullet, "set_angle", 0)
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

function get_table_input()
    local table_input = {
        x = 0,
        y = 0,
        z = 0
    }
    return table_input
end

function handle_move(position)

    old_position = position
    if can_move == false then
        return position
    end
    table_input = get_table_input()
    print(table_input)
    if isInputActive(self, table_input[1]) then
        position.y = position.y - speed
    end
    if isInputActive(self, table_input[2]) then
        position.y = position.y + speed
    end
    if isInputActive(self, table_input[3]) then
        position.x = position.x - speed
    end
    if isInputActive(self, table_input[4]) then
        position.x = position.x + speed
    end
    if position.y > 600 then
        position.y = 600
    end
    if position.y < 0 then
        position.y = 0
    end
    if position.x > 800 then
        position.x = 800
    end
    if position.x < 0 then
        position.x = 0
    end
    return position
end

function get_table_input()
    if hasTag(self, "p1") then 
        table_input = {
            "MoveUp",
            "MoveDown",
            "MoveLeft",
            "MoveRight",
            "Shoot"
        }
    else
        table_input = {
            "MoveUp2",
            "MoveDown2",
            "MoveLeft2",
            "MoveRight2",
            "Shoot2"
        }
    end

    return table_input
end

function damage(dmg)
    hp = hp - dmg
    if self ~= nil and hp < 0 then
        reloadScene("Games/RType/config/scene.json")
    end
end
