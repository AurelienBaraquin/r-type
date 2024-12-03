self = nil
speed = 1
function init(e)
    self = e
end

function update(delta)
    local position = getPosition(self)
    position.x = position.x + 1
    setPosition(self, position)

    if (position.x > 500) then
        destroyEntity(self)
    end
end
