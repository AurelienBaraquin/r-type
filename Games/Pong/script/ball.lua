speed_x = 5
speed_y = 4
self = nil
collisionCooldown = false

function init(e)
    self = e
    print("Ball initialized: " .. e)
end

function update(delta)
    local position = getPosition(self)

    if type(position) ~= "table" then
        print("Position is not a table")
        return
    end

    position.x = position.x + speed_x
    position.y = position.y + speed_y

    if position.y <= 0 or position.y >= 600 - 10 then
        speed_y = -speed_y
    end

    if position.x < 0 or position.x > 800 then
        position.x = 400
        position.y = 300
        randomizeDirection()
        collisionCooldown = false
    end

    setPosition(self, position)
end

function onCollide(other)
    if hasTag(other, "player") and not collisionCooldown then
        print("Collision with player detected!")

        speed_x = -speed_x

        local ballPosition = getPosition(self)
        local playerPosition = getPosition(other)

        if ballPosition.x < playerPosition.x then
            ballPosition.x = playerPosition.x - 20
        else
            ballPosition.x = playerPosition.x + 20
        end

        setPosition(self, ballPosition)

        if ballPosition.y < playerPosition.y then
            speed_y = speed_y - 1
        elseif ballPosition.y > playerPosition.y then
            speed_y = speed_y + 1
        end

        speed_y = math.max(-6, math.min(6, speed_y))

        collisionCooldown = true
    end
end

function randomizeDirection()
    if math.random(0, 1) == 0 then
        speed_x = -math.abs(speed_x)
    else
        speed_x = math.abs(speed_x)
    end

    if math.random(0, 1) == 0 then
        speed_y = -math.abs(speed_y)
    else
        speed_y = math.abs(speed_y)
    end
end
