self = nil
speed = 1
function init(e)
    self = e
end

function update(delta)
    local position = getPosition(self)
    position.x = position.x + 1
    setPosition(self, position)
end
