function update(entity, dt)
    local health = entity:getComponent("Health").value
    local pos = entity:getPosition()

    if health > 50 then
        pos.x = pos.x - 100 * dt
    else
        pos.y = pos.y + 50 * math.sin(pos.x * 0.01)
    end

    entity:setPosition(pos)
end
