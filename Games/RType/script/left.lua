speed = 2
self = e
hp = 0
test = 0
wave = 0
function init(e)
    self = e
    hp = 2
    test = 1
end

function update(delta)
    local position = getPosition(self)
    position.x = position.x - speed
    position.y = position.y + math.sin(wave) * 2
    wave = wave + 0.314/2
    if wave >= 2 * 3.14 then
        wave = 0
    end
    setPosition(self, position)

    if position.x < 50 then
        destroyEntity(self)
    end
end

function onCollide(other)
    if hasTag(other, "player") then
        if hasMethod(other, "damage") then
            callMethod(other, "damage", 1)
            destroyEntity(self)
        end
    end
end

function damage(dmg)
    if test == 0 then
        print("test is 0, not initialized")
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