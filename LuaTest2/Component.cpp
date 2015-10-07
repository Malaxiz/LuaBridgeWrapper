//
//  Component.cpp
//  LuaTest2
//
//  Created by Didrik Munther on 07/10/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include "Component.h"


Component::Component(ComponentScript* script, Entity* parent) : script(script), parent(parent) {
    
    variables.Parse("{}");
    
    if(script->hasReference("variables")) {
        script->script->getReference(script->object + ".variables")->luaRef.push(script->script->getLuaState());
        push(script->script->getLuaState(), luabridge::Nil ());
        while(lua_next(script->script->getLuaState(), -2))
        {
            luabridge::LuaRef key = luabridge::LuaRef::fromStack(script->script->getLuaState(), -2);
            luabridge::LuaRef val = luabridge::LuaRef::fromStack(script->script->getLuaState(), -1);
            lua_pop(script->script->getLuaState(), 1);
            
            auto jsonKey = rapidjson::Value(key.cast<std::string>().c_str(), variables.GetAllocator());
            if(val.isNumber())
                variables.AddMember(jsonKey, val.cast<int>(), variables.GetAllocator());
            else if(val.isString()) {
                auto value = rapidjson::Value(val.cast<std::string>().c_str(), variables.GetAllocator());
                variables.AddMember(jsonKey, value, variables.GetAllocator());
            }
        }
    }
    
    onInit(); // Call init function
    
}

void Component::onInit() {
    if(script->hasReference("onInit"))
        script->references["onInit"]->call(this);
}

void Component::onLoop() {
    if(script->hasReference("onLoop"))
        script->references["onLoop"]->call(this);
}

void Component::onSerialize(rapidjson::Value* v, rapidjson::Document::AllocatorType* alloc) {
    
    if(!script->hasReference("onSerialize"))
        return;
    
    tempV = v;
    tempAlloc = alloc;
    
    script->references["onSerialize"]->call(this);
    
    tempV = nullptr;
    tempAlloc = nullptr;
    
}

void Component::addMember(std::string key, std::string value) {
    
    tempV->AddMember(rapidjson::Value(key.c_str(), *tempAlloc), rapidjson::Value(value.c_str(), *tempAlloc), *tempAlloc);
    
}

rapidjson::Value* Component::getJsonValue(std::string key) {
    if(variables.HasMember(key.c_str())) {
        auto keyValue = rapidjson::Value(key.c_str(), variables.GetAllocator());
        return &variables[keyValue];
    }
    else
        return nullptr;
}

int Component::setVariable(lua_State* L) {
    auto value = getJsonValue(lua_tostring(L, 2));
    
    if(lua_isboolean(L, 3))
        value->SetBool((bool)lua_toboolean(L, 3));
    else if(lua_isnumber(L, 3)) {
        double d = lua_tonumber(L, 3);
        if(static_cast<int>(d) == d)
            value->SetInt((int)d);
        else
            value->SetDouble((double)d);
    }
    else if(lua_isstring(L, 3))
        value->SetString(lua_tostring(L, 3), variables.GetAllocator());
    
    lua_pushnumber(L, 0);
    return 1;
}

int Component::getVariable(lua_State* L) {
    auto value = getJsonValue(lua_tostring(L, 2));
    if(!value) {
        std::stringstream err;
        err << "[ERROR] Variable not found: " << lua_tostring(L, 2);
        std::cout << err.str() << "\n";
        return 1;
    }
    
    if(value->IsBool())
        lua_pushboolean(L, value->GetBool());
    else if(value->IsDouble())
        lua_pushnumber(L, value->GetDouble());
    else if(value->IsInt())
        lua_pushnumber(L, value->GetInt());
    else if(value->IsString())
        lua_pushstring(L, value->GetString());
    else {
        std::stringstream err;
        err << "[ERROR] Variable not pushable: " << lua_tostring(L, 2);
        std::cout << err.str() << "\n";
        return 1;
    }
    
    return 1;
}

