self = nil
speed = 50

background_width = 1769

function init(e)
    collide = nil
    if e == nil then
    end
    self = e
end

function update(delta)
    if self == nil then
        return
    end

    local position = getPosition(self)
    if position == nil then
        return
    end

    position.x = position.x - speed * delta
    setPosition(self, position)

    if position.x <= -background_width then
        position.x = background_width
        setPosition(self, position)
    end
end
