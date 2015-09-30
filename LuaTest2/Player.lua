

player = {
    onLoop = function(this, entity)
        this:say("Hello there mr." .. entity.name .. ", my name is " .. this.name .. ", and my health is at " .. this.health)
        entity.health = entity.health - 1
        -- printMessage("C++ Function")
    end
}