self = nil
function init(e)
    timer = 20
    self = e
    print("init as " .. e)
end

function update(delta)
    timer = timer - 1
    if timer <= 0 then
        destroyEntity(self)
    end
end