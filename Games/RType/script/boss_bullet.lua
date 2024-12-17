local selfEntity = nil
local speed = 4

function init(e)
    selfEntity = e
    print("BossBullet initialized for entity:", selfEntity)
end

function update(delta)
    if selfEntity == nil then
        print("BossBullet entity is nil")
        return
    end

    local position = getPosition(selfEntity)
    position.x = position.x - speed
    setPosition(selfEntity, position)

    if position.x < -100 then
        destroyEntity(selfEntity)
        print("BossBullet destroyed after moving out of bounds")
    end
end

function onCollide(other)
    if hasTag(other, "player") then
        if hasMethod(other, "damage") then
            callMethod(other, "damage", 2)
            print("Player took damage from BossBullet")
        end
        destroyEntity(selfEntity)
        print("BossBullet destroyed after hitting player")
    end
end
