self = e
hp = 100
sprite_entity = nil
can_move = true
enemy_manager = nil

reload_rate = 1
reload_timer = 0

n_bullets = 4
fire_rate = 0.1
fire_timer = 0

function set_enemy_manager(manager)
    enemy_manager = manager
end

function init(e)
    self = e

    sprite_entity = createEntity("BossSprite")
    print("sprite entity" .. sprite_entity)
end

function update(delta)
    local position = getPosition(self)
    handle_movement()
    if reload_timer >= reload_rate then
        handle_fire(delta)
    end
    reload_timer = reload_timer + 1 * delta
    if position.x < 300 then
       can_move = false

    end
end

function handle_fire(delta)
    if n_bullets <= 0 then
        reload_timer = 0
        n_bullets = 4
    end
    fire_timer = fire_timer + 1 * delta
    if fire_timer >= fire_rate then
        bulletPosition = getPosition(self)
        bulletPosition.y = bulletPosition.y + 96
        n_bullets = n_bullets - 1
        fire_timer = fire_timer - fire_rate
        local bullet = createEntity("BossBullet")
        setPosition(bullet, bulletPosition)
        callMethod(bullet, "set_angle", math.pi)
        callMethod(bullet, "set_speed", 3)
        callMethod(bullet, "set_follow_timer", 0.5)
    end
end


function handle_movement()
    if can_move then
        local position = getPosition(self)
        position.x = position.x - 2
        setPosition(self, position)
        position.x = position.x - 64
        setPosition(sprite_entity, position)
    end
end

function damage(dmg)
    hp = hp - dmg
    print("hp: " .. hp)

    if hp <= 0 then
        if self == 0 or self ~= nil then
            local explosion = createEntity("BulletExplosion")
            if hasMethod(enemy_manager, "set_can_spawn") then
                callMethod(enemy_manager, "set_can_spawn", true)
            end
            setPosition(explosion, getPosition(self))
            destroyEntity(sprite_entity)
            destroyEntity(self)
        end
    end
end