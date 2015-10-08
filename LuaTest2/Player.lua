math.randomseed(os.time())
require("Enemy")

game = {

    object = "player",

    references = {
        "onInit",
        "onLoop",
        "onSerialize",
        "variables",
        "doPlayerStuff"
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

    onLoop = function(this)
        this:getParent():say("My name is " .. this:getVariable("name") .. ", and my health is " .. this:getVariable("health"))
    end,

    onSerialize = function(this)
        this:addMember("name", this:getVariable("name"))
        this:addMember("health", this:getVariable("health"))
    end,

    doPlayerStuff = function(this, other)
        otherEnemy = other:getComponent("Enemy.lua")
        enemy.doEnemyStuff(other, this:getParent())
    end
}