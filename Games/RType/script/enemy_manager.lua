local selfEntity = nil
local spawn_timer = 0
local spawn_rate = 50
local boss_spawned = false

function init(e)
    self = e
    print(e)
end

function update(delta)
    if spawn_timer <= 0 then
        spawn_timer = spawn_rate
        if not boss_spawned and math.random(1, 100) > 80 then
            spawnBoss()
            boss_spawned = true
        else
            spawnEnemy()
        end
    end
    if spawn_timer > 0 then
        spawn_timer = spawn_timer - 1
    end
end

function spawnEnemy()
    local enemy = createEntity("Enemy")
    if enemy ~= nil then
        setPosition(enemy, {x = 800, y = math.random(100, 200), z = 0})
        print("Enemy spawned at position:", 800, math.random(100, 200))
    else
        print("Failed to create Enemy entity")
    end
end

function spawnBoss()
    local boss = createEntity("Boss")
    if boss ~= nil then
        setPosition(boss, {x = 800, y = 100, z = 3})
        print("Boss spawned at position:", 800, 100)
    else
        print("Failed to create Boss entity")
    end
end
