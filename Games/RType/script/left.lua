speed = 1
self = e
function init(e)
    self = e
end

function update(delta)
    local position = getPosition(self)
    position.x = position.x - speed
    setPosition(self, position)
end

function onCollide(other)
    print("collided someone")

end
