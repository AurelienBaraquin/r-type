speed_x = -4
speed_y = -3
self = nil
collisionCooldown = false
cooldownTime = 0.5
cooldownTimer = 0

function init(e)
    self = e
    print("Ball initialized: " .. e)
    speed_x = 4
    speed_y = 3
end

function update(delta)
    local position = getPosition(self)

    if type(position) ~= "table" then
        print("Position is not a table")
        return
    end

    position.x = position.x + speed_x
    position.y = position.y + speed_y

    if position.y <= 0 then
        position.y = 0
        speed_y = -speed_y
    elseif position.y >= 600 - 10 then
        position.y = 600 - 10
        speed_y = -speed_y
    end

    if position.x < 0 or position.x > 800 then
        position.x = 200
        position.y = 100
        speed_x = -4
        speed_y = -3
        collisionCooldown = false
    end

    if collisionCooldown then
        cooldownTimer = cooldownTimer + delta
        if cooldownTimer >= cooldownTime then
            collisionCooldown = false
            cooldownTimer = 0
        end
    end

    setPosition(self, position)
end

function onCollide(other)
    if (hasTag(other, "p1") or hasTag(other, "p2")) and not collisionCooldown then
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
