

player = {

    name="Ricky",
    onLoop = function(this, entity)
        this:say("Hello there mr." .. entity.name .. ", my name is " .. this.name)
        printMessage("C++ Function")
    end

}

player2 = {

    name="Morty",
    onLoop = function(this, entity)
        this:say("Hello there mr." .. entity.name .. ", my name is " .. this.name)
    end

}