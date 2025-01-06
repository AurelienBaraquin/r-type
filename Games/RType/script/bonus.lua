self_entity = nil
follow = false
entity_to_follow = nil
timer = 10 * 60
function init(e)
    self_entity = e
    print("init: ", self_entity)
end


function update(delta)
    if follow and entity_to_follow then
        local position = getPosition(entity_to_follow)
        position.x = position.x + 30
        setPosition(self_entity, position)
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

function onCollide(other)
    if hasTag(other, "player") then
        follow = true
        entity_to_follow = other
    end
end