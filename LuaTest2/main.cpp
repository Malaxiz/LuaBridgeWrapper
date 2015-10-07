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
#include "Value.h"


lua_State* L = luaL_newstate();

//int callLuaFunctionFromLua(lua_State* L) {
//    
//    int argc = lua_gettop(L);
//    
//    std::vector<Value> values;
//    for(int i = 1; i <= argc; i++) {
//        if(lua_isboolean(L, i))
//            values.push_back(Value(lua_toboolean(L, i)));
//        else if(lua_isnumber(L, i))
//            values.push_back(Value(lua_tonumber(L, i)));
//        else if(lua_isstring(L, i))
//            values.push_back(Value(lua_tostring(L, i)));
//    }
//    
//    //LuaReference* reference = *((LuaReference**)lua_touserdata(L, 1));
//
//    //lua_getglobal(L, reference->getName());
//    
//    return 1;
//}

int main(int argc, const char* argv[]) {
    
    luaL_openlibs(L);
    
    luabridge::getGlobalNamespace(L)
        .beginClass<Entity>("Entity")
            .addConstructor<void(*)(void)>()
            .addFunction("say", &Entity::say)
            .addCFunction("callCFunction", &Entity::callScriptFunction)
            .addFunction("getComponent", &Entity::getComponent)
            .addFunction("addComponent", &Entity::addComponent)
        .endClass()
        .beginClass<Component>("Component")
            .addCFunction("getVariable", &Component::getVariable)
            .addCFunction("setVariable", &Component::setVariable)
            .addFunction("getParent", &Component::getParent)
            .addFunction("addMember", &Component::addMember);
    
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
    
    myEntity.onLoop();
    myEntity2.onLoop();
    
    // --
    
    rapidjson::Document d;
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
