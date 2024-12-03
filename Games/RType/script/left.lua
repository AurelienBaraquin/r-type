speed = 1
self = e
hp = 0
function init(e)
    self = e
    hp = 3
end

function update(delta)
    local position = getPosition(self)
    position.x = position.x - speed
    setPosition(self, position)
    if canDestroy then
        destroyEntity(self)
    end
end

function onCollide(other)
end

function damage(dmg)
    hp = hp - dmg
    if hp <= 0 then
        destroyEntity(self)
    end
end