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

void Entity::init(LuaScript* script, std::string object) {
    
    this->script = script;
    
    //script->doFile();
    
    script->registerReference(object.c_str(), "name");
    script->registerReference(object.c_str(), "onLoop");
    
    name = script->getReference(object + ".name")->cast<std::string>();
    onLoopFunc = script->getReference(object + ".onLoop");
    
}

void Entity::onLoop(Entity* other) {
    onLoopFunc->call(this, other);
}