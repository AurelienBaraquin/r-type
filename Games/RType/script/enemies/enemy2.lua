speed = 1
self = e
hp = 0
wave = 0
movement = 0.0
angle = 0
distance = 0
init_pos = 0
function init(e)
    self = e
    hp = 20000
end

function set_property(new_angle, new_distance, pos)
    angle = new_angle
    distance = new_distance + 20
    init_pos = pos
end

function set_current_movement(movement)
    current_movement = movement
end

function update(delta)
    local position = getPosition(self)
    movement = movement + delta * 50
    angle = angle + 0.01
    if movement > 1 then
        init_pos = init_pos - 1
        movement = 0
    end
    print(angle)
    position.x = init_pos - distance * math.cos(angle) 
    position.y = 90 + distance * math.sin(angle)
    setPosition(self, position)
    if position.x < -50 then
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