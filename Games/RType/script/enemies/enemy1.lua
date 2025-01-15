speed = 2
self = e
hp = 0
wave = 0
time_movement_change_rate = 0.2
time_movement = 0
movement_table = {-1, -1, 0, 1, 1, 0}
current_movement = 1
function init(e)
    self = e
    hp = 2
end

function set_current_movement(movement)
    current_movement = movement
end

function update(delta)
    if time_movement <= 0 then
        current_movement = (current_movement % 6) + 1
        time_movement = time_movement_change_rate + time_movement
    end
    time_movement = time_movement - 1 * delta
    local position = getPosition(self)
    position.x = position.x - speed
    position.y = position.y + movement_table[current_movement] * speed / 2
    setPosition(self, position)
    if position.x < 50 then
        destroyEntity(self)
    end
end

function onCollide(other)
    if hasTag(other, "player") then
        if hasMethod(other, "damage") then
            callMethod(other, "damage", 1)
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