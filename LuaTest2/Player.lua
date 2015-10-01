math.randomseed(os.time())

game = {

    object = "player",

    references = {
        "onInit",
        "onLoop",
        "onSerialize",
        "variables"
    }

}

player = {

    variables = {
        health = 100,
        name = "EntityName"
    },

    onInit = function(this)
        this:setString("name", tostring(math.random(100)))
    end,

    onLoop = function(this, entity)
        -- printMessage("C++ Function")

        this:say("My name is " .. this:getString("name") .. ", and my health is " .. this:getInt("health"))
        entity:setInt("health", entity:getInt("health") - math.random(30))
    end,

    onSerialize = function(this)
        json = require "json"

        seri = {}
        seri.health = this:getInt("health")
        seri.name = this:getString("name")
        encoded = json.encode(seri)
        return encoded
    end
}