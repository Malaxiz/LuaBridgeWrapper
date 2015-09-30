//
//  main.cpp
//  LuaTest2
//
//  Created by Didrik Munther on 29/09/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include <iostream>

#include "LuaScript.h"
#include "LuaReference.h"

#include "Entity.h"


std::string printMessage(const std::string s) {
    std::cout << s << std::endl;
    return "returned";
}

int main(int argc, const char* argv[]) {
    
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    
    luabridge::getGlobalNamespace(L)
        .beginClass<Entity>("Entity")
            .addConstructor<void(*)(void)>()
            .addProperty("name", &Entity::getName, &Entity::setName)
            .addProperty("health", &Entity::getHealth, &Entity::setHealth)
            .addFunction("say", &Entity::say)
        .endClass()
        .addFunction("printMessage", printMessage);
    
//    LuaScript luaScript("script.lua");
//    
//    luaScript.getNamespace().
//        beginNamespace("game").
//            addFunction("printMessage", printMessage).
//        endNamespace();
//    
//    luaScript.doFile();
//    
//    
//    luaScript.registerReference("test", "sumNumbers");
//    luaScript.registerReference("test", "testString");
//    luaScript.registerReference("test", "testNumber");
//    luaScript.registerReference("test", "testFunction");
//    luaScript.registerReference("test", "asdf", "bla", "var");
//    
//    std::cout << "SumNumbers: " << luaScript.getReference("test.sumNumbers")->call(5, 6) << "\n";
//    std::cout << "TestString: " << luaScript.getReference("test.testString")->cast<std::string>() << "\n";
//    std::cout << "TestNumber: " << luaScript.getReference("test.testNumber")->cast<int>() << "\n";
//    std::cout << "TestFunction: "; luaScript.getReference("test.testFunction")->call();
//    std::cout << "Nested variable: " << luaScript.getReference("test.asdf.bla.var")->cast<std::string>() << "\n";
    
    LuaScript entityScript(L, "Player.lua");
    entityScript.doFile();
    
    // --
    
    Entity myEntity;
    myEntity.init(&entityScript, "player");
    myEntity.setName("Rick");
    
    Entity myEntity2;
    myEntity2.init(&entityScript, "player");
    myEntity2.setName("Morty");
    
    myEntity.onLoop(&myEntity2);
    myEntity2.onLoop(&myEntity);
    
    printMessage(myEntity.onSerialize());
    printMessage(myEntity2.onSerialize());
    
}
