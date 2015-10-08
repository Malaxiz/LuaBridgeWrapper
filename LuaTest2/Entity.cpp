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
    onInit();
}

void Entity::onInit() {
    for(auto& i: components) {
        i.second->onInit();
    }
}

void Entity::onLoop() {
    for(auto& i: components) {
        i.second->onLoop();
    }
}

void Entity::onSerialize(rapidjson::Value* v, rapidjson::Document::AllocatorType* alloc) {
    
    auto componentValues = rapidjson::Value(rapidjson::kObjectType);
    for(auto& i: components) {
        auto component = rapidjson::Value(rapidjson::kObjectType);
        i.second->onSerialize(&component, alloc);
        componentValues.AddMember(rapidjson::Value(i.first.c_str(), *alloc), component, *alloc);
    }
    
    v->AddMember(rapidjson::Value("components", *alloc), componentValues, *alloc);
    
    
//    std::cout << "Is string: " << (*references)["onSerialize"]->call(this).isString() << "\n" <<
//    "Is number: " << (*references)["onSerialize"]->call(this).isNumber() << "\n";
    
//    rapidjson::StringBuffer sb;
//    rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
//    variables.Accept(writer);
//    std::cout << sb.GetString() << "\n";
    
}

void Entity::say(std::string phrase) {
    std::cout << phrase << "\n";
}

void Entity::luaError(lua_State* L, std::string err) {
    std::cout << err << "\n";
    lua_pushstring(L, err.c_str());
}











