speed = 1

function update(e)
    local position = getPosition(e)
    position.x = position.x - speed
    setPosition(e, position)
end

function onCollide(other)
    speed = 10
    if hasMethod(other, "setSpeed") then
        callMethod(other, "setSpeed", 10)
    else
        print("no method")
    end
end
