self = e
hp = 40
sprite_entity = nil
can_move = true
enemy_manager = nil

reload_rate = 1
reload_timer = 0

n_bullets_max = 10
n_bullets = 10
fire_rate = 0.05
fire_timer = 0
time_before_moving = 15

function set_enemy_manager(manager)
    enemy_manager = manager
end

function init(e)
    self = e
    sprite_entity = createEntity("BossSprite")
    addTag(sprite_entity, "my_scene")
    print("sprite entity" .. sprite_entity)
end

function update(delta)
    if can_move == false and time_before_moving > 0 then
        time_before_moving = time_before_moving - 1 * delta
    end
    if time_before_moving <= 0 and can_move == false then
        vector = {x = -2, y = 0}
        move(vector)
    end
    
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

function move(vector)
    local position = getPosition(self)
    position.x = position.x + vector.x
    position.y = position.y + vector.y
    setPosition(self, position)
    position.x = position.x - 64
    setPosition(sprite_entity, position)
end

function handle_fire(delta)
    if n_bullets <= 0 then
        reload_timer = 0
        n_bullets = n_bullets_max
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

function onCollide(other)
    if hasTag(other, "player") then
        if hasMethod(other, "damage") then
            reloadScene("Games/RType/config/scene.json")
        end
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
            changeScene("Games/RType/config/scene2.json")
        end
    end
end