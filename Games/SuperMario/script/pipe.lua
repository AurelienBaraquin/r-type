speed = -2
self = nil

function init(e)
    self = e
end

function update(delta)
    local position = getPosition(self)
    position.x = position.x + speed
    if position.x < -52 then
        position.x = 800
    end
    setPosition(self, position)
end
