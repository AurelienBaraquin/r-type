self = nil
speed = 1
collide = nil
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
     position.x = position.x + 5
    setPosition(self, position)

    if (position.x > 800) then

    end
end

function onCollide(other)
    if hasTag(other, "enemy") then
        collide = other
        if hasMethod(other, "damage") then
            callMethod(other, "damage", 1)
        end
        if self ~= nil then
            destroyEntity(self)
        end
    end
end