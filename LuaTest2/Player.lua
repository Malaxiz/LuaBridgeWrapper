math.randomseed(os.time())

player = {
    onLoop = function(this, entity)
        this:say("Hello there mr." .. entity.name .. ", my name is " .. this.name .. ", and my health is at " .. this.health)
        entity.health = entity.health - math.random(30)
        -- printMessage("C++ Function")
    end,

    onSerialize = function(this)
        json = require "json"

        seri = {}
        seri.health = this.health
        seri.name = this.name
        encoded = json.encode(seri)
        return encoded
    end
}