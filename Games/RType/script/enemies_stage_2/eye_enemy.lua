self = nil
speed = 1
collide = nil
enemy_dmg = 1
hp = 1
function init(e)
    hp = 1
    collide = nil
    if e == nil then
        print("self is nil")
    end
    self = e

end

function update(delta)
    if self == nil then
        print("self is nil")
    end
    local position = getPosition(self)
     position.x = position.x - 4
    setPosition(self, position)

    if (position.x < -64) then
        destroyEntity(self)
    end
end


function onCollide(other)
    if hasTag(other, "player") then
        collide = other
        if hasMethod(other, "damage") then
            callMethod(other, "damage", enemy_dmg)
        end
        if self ~= nil then
            destroyEntity(self)
        end
    end
end

function damage(dmg)
    if self == nil then
        print("self is nil")
    end
    hp = hp - dmg

    if hp <= 0 then

        if self == 0 or self ~= nil then
            local explosion = createEntity("BulletExplosion")
            setPosition(explosion, getPosition(self))
            destroyEntity(self)
            
        end
    end
end