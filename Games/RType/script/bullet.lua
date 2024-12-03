self = nil
speed = 1
function init(e)
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

    if (position.x > 1500) then
        destroyEntity(self)
    end
end

function onCollide(other)
end