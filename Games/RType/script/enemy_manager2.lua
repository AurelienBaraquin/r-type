local selfEntity = nil
local spawn_timer = 0
local spawn_rate = 1
local shooter_spawned = false
local wave = 0
local can_spawn = true

function init(e)
    
    self = e
end

function update(delta)
    if spawn_timer <= 0 and can_spawn then
        spawn_timer = spawn_timer + spawn_rate
        enemy = spawnEnemy()
    end
    spawn_timer = spawn_timer - 1 * delta
end

function set_can_spawn(value)
    can_spawn = value
end

function spawnEnemy()
    spawnEnemyByName("eye_enemy", 384, math.random(0, 180))

    wave = wave + 1
end

function spawnEnemyByName(enemyName, x, y)
    local enemy = createEntity(enemyName)
    addTag(enemy, "MainScene")
    setPosition(enemy, {x = x, y = y, z = 0})
    return enemy
end
