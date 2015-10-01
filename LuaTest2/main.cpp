//
//  main.cpp
//  LuaTest2
//
//  Created by Didrik Munther on 29/09/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include <iostream>
#include <vector>

#include "LuaScript.h"
#include "LuaReference.h"
#include "EntityScript.h"

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
            .addFunction("say", &Entity::say)
            .addFunction("getString", &Entity::getStringVariable)
            .addFunction("setString", &Entity::setStringVariable)
            .addFunction("getInt", &Entity::getIntVariable)
            .addFunction("setInt", &Entity::setIntVariable)
        .endClass()
        .addFunction("printMessage", printMessage);

    // --
    
    LuaScript script(L, "Player.lua");
    script.doFile();
    
    EntityScript entityScript(&script);
    
    // --
    
    Entity myEntity;
    myEntity.init(&entityScript, "player");
    
    Entity myEntity2;
    myEntity2.init(&entityScript, "player");
    
    myEntity.onLoop(&myEntity2);
    myEntity2.onLoop(&myEntity);
    myEntity.onLoop(&myEntity2);
    myEntity2.onLoop(&myEntity);
    myEntity.onLoop(&myEntity2);
    myEntity2.onLoop(&myEntity);
    
    printMessage(myEntity.onSerialize());
    printMessage(myEntity2.onSerialize());
    
}
