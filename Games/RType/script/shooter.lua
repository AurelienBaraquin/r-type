local selfEntity = nil
local speed = 2
local hp = 10
local shoot_timer = 0
local shoot_rate = 30
local move_direction = 1
local move_timer = 0
local move_duration = 60

function init(e)
    selfEntity = e
    hp = 10
    print("Shooter initialized for entity:", selfEntity, "with HP:", hp)
end

function update(delta)
    if selfEntity == nil then
        print("Shooter entity is nil")
        return
    end

    move_timer = move_timer + 1
    if move_timer >= move_duration then
        move_timer = 0
        move_direction = -move_direction
    end

    local position = getPosition(selfEntity)
    position.y = position.y + speed * move_direction
    setPosition(selfEntity, position)

    if position.y < 100 then
        position.y = 100
        move_direction = 1
    elseif position.y > 500 then
        position.y = 500
        move_direction = -1
    end
    setPosition(selfEntity, position)

    shoot_timer = shoot_timer + 1
    if shoot_timer >= shoot_rate then
        shoot_timer = 0
        shoot()
    end
end

function shoot()
    if selfEntity == nil then
        print("Cannot shoot, shooter entity is nil")
        return
    end

    local position = getPosition(selfEntity)
    local bullet_position = {
        x = position.x - 50,
        y = position.y,
        z = position.z
    }

    local bullet = createEntity("ShooterBullet")
    addTag(bullet, "shooter_bullet")

    if bullet ~= nil then
        setPosition(bullet, bullet_position)
        print("Shooter shot a bullet from position:", bullet_position.x, bullet_position.y)
    else
        print("Failed to create ShooterBullet entity")
    end
end

function onCollide(other)
    if hasTag(other, "bullet") then
        damage(1)
        print("Shooter hit by bullet:", other)
        destroyEntity(other)
    end
end

function damage(dmg)
    if selfEntity == nil then
        print("Cannot apply damage, shooter entity is nil")
        return
    end

    hp = hp - dmg
    print("Shooter took damage:", dmg, "remaining HP:", hp)

    if (hp <= 0) then
        destroyEntity(selfEntity)
        print("Shooter destroyed")
    end
end

function findPlayerEntity()
    local players = getEntitiesWithTag("player")
    if #players > 0 then
        return players[1]
    end
    return nil
end

function calculateDirection(shooterPos, playerPos)
    local dx = playerPos.x - shooterPos.x
    local dy = playerPos.y - shooterPos.y
    local magnitude = math.sqrt(dx * dx + dy * dy)

    if magnitude == 0 then
        return {x = 0, y = 1}
    else
        return {x = dx / magnitude, y = dy / magnitude}
    end
end
