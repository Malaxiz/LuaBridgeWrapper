//
//  Entity.cpp
//  LuaTest2
//
//  Created by Didrik Munther on 30/09/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include "Entity.h"


Entity::Entity() {
    health = 100;
}

void Entity::init(LuaScript* script, std::string object) {
    
    onLoopFunc = script->registerReference(object.c_str(), "onLoop");
    onSerializeFunc = script->registerReference(object.c_str(), "onSerialize");
    
}

void Entity::onLoop(Entity* other) {
    onLoopFunc->call(this, other);
}

std::string Entity::onSerialize() {
    return onSerializeFunc->call(this);
}