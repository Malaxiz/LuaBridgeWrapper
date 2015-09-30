//
//  Entity.cpp
//  LuaTest2
//
//  Created by Didrik Munther on 30/09/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include "Entity.h"


Entity::Entity() {
    
}

Entity::~Entity() {
    delete script;
}

void Entity::init(std::string scriptPath, std::string object) {
    
    script = new LuaScript(scriptPath);
    
    script->getNamespace()
        .beginClass<Entity>("Entity")
            .addConstructor<void(*)(void)>()
            .addProperty("name", &Entity::getName, &Entity::setName)
            .addProperty("health", &Entity::getHealth, &Entity::setHealth)
            .addFunction("say", &Entity::say)
        .endClass();
    
    script->doFile();
    
    script->registerReference(object.c_str(), "name");
    script->registerReference(object.c_str(), "onLoop");
    
    name = script->getReference(object + ".name")->cast<std::string>();
    onLoopFunc = script->getReference(object + ".onLoop");
    
}

void Entity::onLoop(Entity* other) {
    onLoopFunc->call(this, other);
}