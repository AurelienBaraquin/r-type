function update(e)
    local animation = getAnimation(e)
    if animation.playing == false then
        playAnimation(e, 0)
    end
end
