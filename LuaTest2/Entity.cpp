//
//  Entity.cpp
//  LuaTest2
//
//  Created by Didrik Munther on 30/09/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include "Entity.h"


Entity::Entity() {
    health = 5;
}

void Entity::init(LuaScript* script, std::string object) {
    
    script->registerReference(object.c_str(), "onLoop");
    
    onLoopFunc = script->getReference(object + ".onLoop");
    
}

void Entity::onLoop(Entity* other) {
    onLoopFunc->call(this, other);
}