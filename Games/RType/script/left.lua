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
    speed = 10
    if hasMethod(other, "setSpeed") then
        callMethod(other, "setSpeed", 10)
    else
        print("no method")
    end
end
