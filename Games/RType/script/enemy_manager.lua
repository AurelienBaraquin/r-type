local selfEntity = nil
local spawn_timer = 0
local spawn_rate = 4
local shooter_spawned = false
local wave = 0
local can_spawn = true

function init(e)
    self = e
end

function update(delta)
    if spawn_timer <= 0 and can_spawn then
        spawn_timer = spawn_rate
        enemy = spawnEnemy()
    end
    spawn_timer = spawn_timer - 1 * delta
end

function set_can_spawn(value)
    can_spawn = value
end

function spawnEnemy()
    local enemyType = math.random(1, 2) == 1 and "Enemy1" or "Enemy"
    if wave ~= 0 then 
        if wave % 50 == 0 then
            enemyType = "Boss"
            can_spawn = false
        elseif wave % 10 == 0 then
            enemyType = "EnemyRound"
        elseif wave % 5 == 0 then 
            enemyType = "Shooter"
        end
    end
    enemyType = "Boss"
    can_spawn = false
    wave = wave + 1

    if enemyType == "EnemyRound" then
        return spawnEnemyCircle()
    elseif enemyType == "Boss" then
        boss = spawnEnemyByName("Boss", 384, 30)
        if hasMethod(boss, "set_enemy_manager") then
            callMethod(boss, "set_enemy_manager", self)
        end
        return boss
    elseif enemyType == "Enemy1" then
        return spawnEnemy1Hord()
    elseif enemyType == "Shooter" then
        return spawnShooter()
    else
        return spawnEnemyByName(enemyType, 384, math.random(0, 180))
    end
end

function spawnEnemy1Hord()
    y = math.random(0, 180)
    for i = 1, 4 do
        local enemy = spawnEnemyByName("Enemy1", 384 + i * 30, y)
        callMethod(enemy, "set_current_movement", i % 6 + 1)
    end
end

function spawnEnemyCircle()
    gap = 3.14 * 2 / 11
    for i = 1, 10 do
        local enemy = spawnEnemyByName("EnemyRound", 500 + math.cos(gap * i) * 110, 90 + 24 + math.sin(gap * i) * 110)
        callMethod(enemy, "set_property", gap * i, 110, 500)

        print("Spawning enemy: ", enemy)
    end
end

function spawnEnemyByName(enemyName, x, y)
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
