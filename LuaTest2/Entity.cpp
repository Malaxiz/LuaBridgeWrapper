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

void Entity::init(EntityScript* script) {
    
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
    
    references = script->references;
    
    if(hasReference("onInit"))
        references["onInit"]->call(this); // Call init function
    
}

void Entity::onLoop(Entity* other) {
    if(hasReference("onLoop"))
        references["onLoop"]->call(this, other);
}

std::string Entity::onSerialize() {
    if(hasReference("onSerialize"))
        return references["onSerialize"]->call(this);
    else
        return "";
    
//    rapidjson::StringBuffer sb;
//    rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
//    variables.Accept(writer);
//    std::cout << sb.GetString() << "\n";
}