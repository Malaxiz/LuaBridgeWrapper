

player = {

    name="Ricky",
    onLoop = function(this, entity)
        entity:say("Hello there mr." .. entity.name .. ", my name is " .. this.name)
    end

}

player2 = {

    name="Morty",
    onLoop = function(this, entity)
        entity:say("Hello there mr." .. entity.name .. ", my name is " .. this.name)
    end

}