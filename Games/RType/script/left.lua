speed = 2
self = e
hp = 0
test = 0
function init(e)
    self = e
    hp = 2
    test = 1
end

function update(delta)
    local position = getPosition(self)
    position.x = position.x - speed
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
            destroyEntity(self)
        end
    end
end