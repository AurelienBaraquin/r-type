self = nil
speed = 10
collide = nil
damage = 1
angle = 0
function init(e)
    collide = nil
    if e == nil then
        print("self is nil")
    end
    self = e

end

function update(delta)
    if self == nil then
        print("self is nil")
    end
    local position = getPosition(self)
    position.y = position.y + math.sin(angle) * speed
    position.x = position.x + math.cos(angle) * speed
    setPosition(self, position)

    if (position.x > 800) then
        destroyEntity(self)
    end
end

function set_angle(new_angle)
    angle = new_angle
    print("angle: ", angle)
end

function onCollide(other)
    if hasTag(other, "enemy") then
        collide = other
        if hasMethod(other, "damage") then
            callMethod(other, "damage", damage)
        end
        if self ~= nil then
            destroyEntity(self)
        end
    end
end