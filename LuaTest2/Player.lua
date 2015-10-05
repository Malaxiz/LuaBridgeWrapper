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
        a = this:callCFunction("aaaa", 5.05, "123231111", 1234)
        print(a)

        --this:say("My name is " .. this:getString("name") .. ", and my health is " .. this:getInt("health"))
    end,

    onSerialize = function(this)
        json = require "json"

        seri = {}
        seri.name = this:getString("name")
        seri.health = this:getInt("health")
        encoded = json.encode(seri)
        return encoded
    end
}