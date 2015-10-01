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


lua_State* L = luaL_newstate();

void printMessage(const std::string s) {
    std::cout << s << std::endl;
//    //return "returned";
//    
//    luaL_Buffer b;
//    luaL_buffinit(L, &b);
//    luaL_pushresult(&b);
//    luaL_addvalue(&b);
}

int main(int argc, const char* argv[]) {
    
    luaL_openlibs(L);
    
    luabridge::getGlobalNamespace(L)
        .beginClass<Entity>("Entity")
            .addConstructor<void(*)(void)>()
            .addFunction("say", &Entity::say)
            .addFunction("getString", &Entity::getStringVariable)
            .addFunction("setString", &Entity::setStringVariable)
            .addFunction("getInt", &Entity::getIntVariable)
            .addFunction("setInt", &Entity::setIntVariable)
            .addFunction("getReference", &Entity::getReference)
        .endClass()
        .addFunction("printMessage", printMessage);

    // --
    
    LuaScript eneScript(L, "Enemy.lua");
    LuaScript entScript(L, "Player.lua");
    
    EntityScript entityScript(&entScript);
    EntityScript enemyScript(&eneScript);
    
    // --
    
    Entity myEntity;
    myEntity.init(&entityScript);
    
    Entity myEntity2;
    myEntity2.init(&enemyScript);
    
    while(myEntity.getIntVariable("health") > 0) { // Loop and let enemy attack player
        myEntity.onLoop(&myEntity2);
        myEntity2.onLoop(&myEntity);
    }
    
    printMessage(myEntity.onSerialize());
    printMessage(myEntity2.onSerialize()); // Will not run, because enemy does not have a seralize function
    
}
