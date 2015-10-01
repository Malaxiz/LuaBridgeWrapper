//
//  Entity.cpp
//  LuaTest2
//
//  Created by Didrik Munther on 30/09/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include <map>

#include "Entity.h"


Entity::Entity() {
    variables.Parse("{}");
}

void Entity::init(EntityScript* script, std::string object) {
    
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
    
    onLoopFunc = script->hasReference("onLoop") ? script->script->getReference(object + ".onLoop") : nullptr;
    onSerializeFunc = script->hasReference("onSerialize") ? script->script->getReference(object + ".onSerialize") : nullptr;
    onInitFunc = script->hasReference("onInit") ? script->script->getReference(object + ".onInit") : nullptr;
    
    if(onInitFunc)
        onInitFunc->call(this); // Call init function
    
}

void Entity::onLoop(Entity* other) {
    if(onLoopFunc)
        onLoopFunc->call(this, other);
}

std::string Entity::onSerialize() {
    if(onSerializeFunc)
        return onSerializeFunc->call(this);
    else
        return "";
    
//    rapidjson::StringBuffer sb;
//    rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
//    variables.Accept(writer);
//    std::cout << sb.GetString() << "\n";
}