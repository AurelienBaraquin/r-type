local speed = 100
local amplitude = 50
local frequency = 2

function update(entity, dt)
    local pos = entity:getPosition()
    pos.x = pos.x - speed * dt
    pos.y = pos.y + amplitude * math.sin(frequency * pos.x * 0.01)
    entity:setPosition(pos)
end
