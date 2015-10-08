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

#include "Entity.h"
#include "Component.h"

using namespace rapidjson;


lua_State* L = luaL_newstate();

int main(int argc, const char* argv[]) {
    
    luaL_openlibs(L);
    
    luabridge::getGlobalNamespace(L)
        .beginClass<Entity>("Entity")
            .addConstructor<void(*)(void)>()
            .addFunction("say", &Entity::say)
            .addFunction("getComponent", &Entity::getComponent)
            .addFunction("addComponent", &Entity::addComponent)
        .endClass()
        .beginClass<Component>("Component")
            .addCFunction("getVariable", &Component::getVariable)
            .addCFunction("setVariable", &Component::setVariable)
            .addFunction("getParent", &Component::getParent)
            .addFunction("addMember", &Component::addMember)
        .endClass();
    
    // --
    
    LuaScript enemyLuaScript(L, "Enemy.lua");
    LuaScript entityLuaScript(L, "Player.lua");
    
    ComponentScript entityScript(&entityLuaScript);
    ComponentScript enemyScript(&enemyLuaScript);
    
    // --
    
    Entity myEntity;
    myEntity.addComponent(&entityScript);
    myEntity.addComponent(&enemyScript);
    
    Entity myEntity2;
    myEntity2.addComponent(&enemyScript);
    
//    myEntity.onLoop();
//    myEntity2.onLoop();
    
    myEntity.getComponent("Player.lua")->getScript()->getReference("doPlayerStuff")->call(myEntity.getComponent("Player.lua"), myEntity2);
    
    // --
    
    Document d;
    d.Parse("{}");
    
    rapidjson::Value entityValue(rapidjson::kObjectType);
    myEntity.onSerialize(&entityValue, &d.GetAllocator());
    myEntity2.onSerialize(&entityValue, &d.GetAllocator());
    
    d.AddMember("entities", entityValue, d.GetAllocator());
    
    rapidjson::StringBuffer sb;
    rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
    d.Accept(writer);
    
    std::cout << sb.GetString() << "\n";
    
}
