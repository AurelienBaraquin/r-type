local selfEntity = nil
local spawn_timer = 0
local spawn_rate = 2
local shooter_spawned = false

function init(e)
    self = e
    print(e)
end

function update(delta)
    if spawn_timer <= 0 then
        spawn_timer = spawn_rate
        enemy = spawnEnemy()
    end
    spawn_timer = spawn_timer - 1 * delta
end


function spawnEnemy()
    local enemyType = math.random(1, 2) == 1 and "Enemy1" or "Enemy"
    if enemyType == "Enemy1" then
        return spawnEnemy1Hord()
    else
        return spawnEnemyByName(enemyType, 384, math.random(0, 180))
    end
end

function spawnEnemy1Hord()
    y = math.random(0, 180)
    for i = 1, 5 do
        local enemy = spawnEnemyByName("Enemy1", 384 + i * 30, y)
        callMethod(enemy, "set_current_movement", i % 6 + 1)
    end
end

function spawnEnemyByName(enemyName, x, y)
    print("Spawning enemy: ", enemyName)
    local enemy = createEntity(enemyName)
    addTag(enemy, "MainScene")
    setPosition(enemy, {x = x, y = y, z = 0})
    return enemy
end

function spawnShooter()
    local shooter = createEntity("Shooter")
    addTag(shooter, "MainScene")
    setPosition(shooter, {x = 220, y = 30, z = 3})
    return shooter
end
