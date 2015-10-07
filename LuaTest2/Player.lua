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
        this:setVariable("name", tostring(math.random(20)))
    end,

    onLoop = function(this, entity)
        --a = this:callCFunction("aaaa", 5.05, "123231111", 1234)
        --print(a)

        this:getParent():say("My name is " .. this:getVariable("name") .. ", and my health is " .. this:getVariable("health"))
    end,

    onSerialize = function(this)
        this:addMember("name", this:getVariable("name"))
        this:addMember("health", this:getVariable("health"))

        --json = require "json"

        --seri = {}
        --seri.name = this:getVariable("name")
        --seri.health = this:getVariable("health")
        --encoded = json.encode(seri)
        --return encoded
    end
}