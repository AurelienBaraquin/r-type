local selfEntity = nil
local speed = 4
local angle = 0
function init(e)
    selfEntity = e
end

function set_angle(a)
    angle = a
end

set_damage = function(dmg)
    damage = dmg
end

set_speed = function(s)
    speed = s
end

function update(delta)
    if selfEntity == nil then
        return
    end

    local position = getPosition(selfEntity)
    old_x = position.x
    if (angle == 0) then
        print("angle: " .. angle)
    end
    position.x = position.x + speed * math.cos(angle)
    position.y = position.y + speed * math.sin(angle)
    setPosition(selfEntity, position)

    if position.x < -100 or position.x > 800 or position.y < -100 or position.y > 600 then
        destroyEntity(selfEntity)
    end
end

function onCollide(other)
    if hasTag(other, "player") then
        if hasMethod(other, "damage") then
            callMethod(other, "damage", 1)
        end
        destroyEntity(selfEntity)
    end
end
