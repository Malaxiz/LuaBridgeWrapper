math.randomseed(os.time())

game = {

    object = "enemy",

    references = {
        "variables",
        "onLoop"
    }

}

enemy = {

    variables = {
        health = 100,
        name = "EnemyName"
    },

    onLoop = function(this, entity)
        --this:say("My name is " .. this:getString("name") .. ", and I am an enemy")
        entity:setInt("health", entity:getInt("health") - math.random(20))
    end

    

}