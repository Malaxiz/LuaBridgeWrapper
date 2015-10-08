math.randomseed(os.time())

game = {

    object = "enemy",

    references = {
        "variables",
        "onLoop",
        "onInit",
        "onSerialize",
        "doEnemyStuff"
    }

}

enemy = {

    variables = {
        health = 100,
        name = "EnemyName"
    },

    onInit = function(this)
        this:setVariable("name", math.random(50))
    end,

    onLoop = function(this)
        this:getParent():say("My name is " .. this:getVariable("name") .. ", and I am an enemy")
    end,

    onSerialize = function(this)
        this:addMember("name", this:getVariable("name"))
    end,

    doEnemyStuff = function(this, other)
        playerComponent = other:getComponent("Player.lua")
        playerComponent:setVariable("health", playerComponent:getVariable("health") - 20)
    end

}