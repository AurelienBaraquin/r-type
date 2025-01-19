speed = 3
self = nil

function init(e)
    self = e
    print("init as " .. e)
end

function update(delta)
    local position = getPosition(self)

    if type(position) ~= "table" then
        print("Position is not a table")
        return
    end

    position = handle_move(position)
    setPosition(self, position)
end

function handle_move(position)
    if isInputActive(self, "MoveUp") then
        position.y = position.y - speed
    end
    if isInputActive(self, "MoveDown") then
        position.y = position.y + speed
    end

    if position.y < 0 then
        position.y = 0
    end
    if position.y > 450 - 50 then
        position.y = 450 - 50
    end

    return position
end
