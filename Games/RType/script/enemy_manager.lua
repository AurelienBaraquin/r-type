local selfEntity = nil
local spawn_timer = 0
local spawn_rate = 50
local shooter_spawned = false

function init(e)
    self = e
    print(e)
end

function update(delta)
    if spawn_timer <= 0 then
        spawn_timer = spawn_rate
        if not shooter_spawned and math.random(1, 100) > 80 then
            spawnShooter()
            shooter_spawned = true
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
    addTag(enemy, "MainScene")
    if enemy ~= nil then
        setPosition(enemy, {x = 384, y = math.random(0, 180), z = 0})
    else
        print("Failed to create Enemy entity")
    end
end

function spawnShooter()
    local shooter = createEntity("Shooter")
    addTag(shooter, "MainScene")

    if shooter ~= nil then
        print("SPAWNED")
        setPosition(shooter, {x = 220, y = 30, z = 3})
    else
        print("Failed to create Shooter entity")
    end
end
