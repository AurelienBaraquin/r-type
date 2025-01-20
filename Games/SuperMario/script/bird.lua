gravity = 0.5
jump_strength = -10
velocity = 0
self = nil

function init(e)
    self = e
end

function update(delta)
    local position = getPosition(self)
    velocity = velocity + gravity
    if isInputActive(self, "Jump") then
        velocity = jump_strength
    end
    position.y = position.y + velocity
    setPosition(self, position)
end
