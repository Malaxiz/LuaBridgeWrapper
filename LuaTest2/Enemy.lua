math.randomseed(os.time())

game = {

    object = "enemy",

    references = {
        "variables",
        "onLoop",
        "onInit",
        "onSerialize"
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

    onLoop = function(this, entity)
        this:getParent():say("My name is " .. this:getVariable("name") .. ", and I am an enemy")
    end,

    onSerialize = function(this)
        this:addMember("name", this:getVariable("name"))
    end

}