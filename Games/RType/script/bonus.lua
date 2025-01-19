self_entity = nil
follow = false
entity_to_follow = nil
timer = 10 * 60

bullet_type = 1

fire_rate = 0.2
fire_timer = 0

position = nil
function init(e)
    self_entity = e
    print("init: ", self_entity)
end


function update(delta)
    position = getPosition(self_entity)
    if follow and entity_to_follow then
        local position = getPosition(entity_to_follow)
        position.x = position.x + 30
        setPosition(self_entity, position)

        if bullet_type == 0 then
            handle_bonus_bullet_straight()
        elseif bullet_type == 1 then
            handle_bonus_bullet_diagonal(delta)
        end
    end
    
end

function onCollide(other)
    if hasTag(other, "player") then
        follow = true
        entity_to_follow = other
        print("follow: ", entity_to_follow)
    end
end

function handle_bonus_bullet_straight()
    if follow and entity_to_follow then
        timer = timer - 1
        if math.fmod(timer, 5) == 0 then
            bullet = createEntity("BonusBullet")
            setPosition(bullet, position)
        end
        if timer <= 0 then
            destroyEntity(self_entity)
        end
    end
end

function handle_bonus_bullet_diagonal(delta)
    timer = timer - 0.05
    if timer <= 0 then
        destroyEntity(self_entity)
    end
    if fire_timer >= fire_rate then
        fire_timer = 0
    else 
        fire_timer = fire_timer + 1 * delta
        return
    end
    bullet1 = createEntity("BonusBullet")
    callMethod(bullet1, "set_angle", math.pi / 5)
    setPosition(bullet1, position)
    bullet = createEntity("BonusBullet")
    callMethod(bullet, "set_angle", -math.pi / 5)
    setPosition(bullet, position)
end