
self = nil
spawn_timer = 0
spawn_rate = 50
function init(e)
    self = e
    print(e)
end

function update(delta)
    if spawn_timer <= 0 then
        spawn_timer = spawn_rate
        enemy = createEntity("Enemy")
        setPosition(enemy, {x = 800, y = math.random(100, 200)})
    end
    if spawn_timer > 0 then
        spawn_timer = spawn_timer - 1
    end
end