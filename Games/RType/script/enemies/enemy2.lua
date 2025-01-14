speed = 1
self = e
hp = 0
wave = 0
movement = 0.0
angle = 0
distance = 0
init_pos = 0

fire_rate = 10
fire_timer = 0
function init(e)
    self = e
    hp = 20000
end

function set_property(new_angle, new_distance, pos)
    angle = new_angle
    print(new_angle)
    fire_timer = 4 * (new_angle / (2 * 3.14))
    print(fire_timer)
    distance = new_distance + 20
    init_pos = pos
end

function set_current_movement(movement)
    current_movement = movement
end

function update(delta)
    local position = getPosition(self)
    movement = movement + delta * 50
    angle = angle + 0.012
    if movement > 1 then
        init_pos = init_pos - 1
        movement = 0
    end
    
    if fire_timer >= fire_rate then
        fire_timer = 0
        shoot()
    end
    
    fire_timer = fire_timer + delta


    position.x = init_pos - distance * math.cos(angle) 
    position.y = 90 + distance * math.sin(angle)
    setPosition(self, position)
    if position.x < -200 then
        destroyEntity(self)
    end
end

function onCollide(other)
    if hasTag(other, "player") then
        if hasMethod(other, "damage") then
            callMethod(other, "damage", 3)
            destroyEntity(self)
        end
    end
end

function damage(dmg)
    if test == 0 then
        print("test is 0, not initialized")
    end
    hp = hp - dmg

    if hp <= 0 then

        if self == 0 or self ~= nil then
            local explosion = createEntity("BulletExplosion")
            setPosition(explosion, getPosition(self))
            destroyEntity(self)
        end
    end
end

function shoot()
    local position = getPosition(self)
    local bullet_position = {
        x = position.x - 10,
        y = position.y,
        z = position.z
    }
    bullet = createEntity("EnemyBullet")
    addTag(bullet, "MainScene")
    
    setPosition(bullet, bullet_position)
    
    local players = getEntitiesByTag("player")
    if #players == 0 then
        print("no player found")
        return
    end
    
    local player = players[1]
    local player_position = getPosition(player)
    local angle = 0
    angle = math.atan(player_position.y - position.y, player_position.x - position.x)
    callMethod(bullet, "set_angle", angle)
    callMethod(bullet, "set_speed", 2)
end