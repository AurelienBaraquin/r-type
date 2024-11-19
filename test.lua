function update(e)
    local animation = getAnimation(e)
    if animation.playing == false then
        animation.playing = true
    end
    setAnimation(e, animation)
end
