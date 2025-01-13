local selfEntity = nil
local speed = 4
local angle = 0
local follow_delay = 0
local follow_timer = 0
local player_position = nil
function init(e)
    selfEntity = e
    follow_delay = 0.0
end

function set_angle(a)
    angle = a
end

function set_damage(dmg)
    damage = dmg
end

function set_speed(s)
    speed = s
end

function set_follow_timer(timer)
    print("set follow timer")
    follow_timer = timer
end



function update(delta)
    y = 0
    if selfEntity == nil then
        return
    end
    if follow_delay < follow_timer then
        print("follow delay")
        follow_delay = follow_delay + 1 * delta
        followPlayer(selfEntity)
    end

    if follow_delay >= follow_timer and follow_timer ~= 0 then
        if math.abs(player_position.y - getPosition(selfEntity).y) < 5 then
            y = 0
        elseif player_position.y > getPosition(selfEntity).y then
            y = 1
        elseif player_position.y < getPosition(selfEntity).y then
           y = -1
        else
            y = 0
        end
    end

    local position = getPosition(selfEntity)
    old_x = position.x
    if (angle == 0) then
        print("angle: " .. angle)
    end
    position.x = position.x + speed * math.cos(angle)
    position.y = position.y + speed * math.sin(angle) + y * speed
    setPosition(selfEntity, position)

    if position.x < -100 or position.x > 800 or position.y < -100 or position.y > 600 then
        destroyEntity(selfEntity)
    end
end

function followPlayer(self)
    print("follow player")
    local players = getEntitiesByTag("player")
    if #players == 0 then
        return 0
    end
    
    local player = players[1]
    player_position = getPosition(player)
    if player_position.y  > getPosition(selfEntity).y then
        return 1
    end
    if player_position.y < getPosition(selfEntity).y then
        return -1
    end
end

function onCollide(other)
    if hasTag(other, "player") then
        if hasMethod(other, "damage") then
            callMethod(other, "damage", 1)
        end
        destroyEntity(selfEntity)
    end
end
