-- script.lua


-- game.printMessage("You can call C++ functions from Lua!")


test = {}

test.sumNumbers = function(a,b)
        return a + b
    end

test.testString = "LuaBridge works!"
test.testNumber = 5
test.testFunction = function()
        game.printMessage(game.printMessage("You can still call C++ functions from Lua functions!"))
    end