//
//  Entity.h
//  LuaTest2
//
//  Created by Didrik Munther on 30/09/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#ifndef __LuaTest2__Entity__
#define __LuaTest2__Entity__

#include <stdio.h>
#include <map>

#include "LuaScript.h"
#include "LuaReference.h"
#include "ComponentScript.h"
#include "Component.h"


class Entity {
    
public:
    Entity();
    
    void onInit();
    void onLoop();
    void onSerialize(rapidjson::Value* v, rapidjson::Document::AllocatorType* alloc);
    
    void say(std::string phrase);
    
    void luaError(lua_State* L, std::string err);
    
    
    
    // --------------------------------------------------- //
    
    std::map<std::string, Component*> components;
    
    Component* addComponent(ComponentScript* componentScript) {
        Component* component = new Component(componentScript, this);
        components[componentScript->script->getScriptName()] = component;
        return component;
    }
    
    Component* getComponent(std::string componentName) {
        if(hasComponent(componentName))
            return components[componentName];
        else
            return nullptr;
    }
    
    bool hasComponent(std::string scriptName) {
        return components.find(scriptName) != components.end();
    }
    
private:
    
};

#endif /* defined(__LuaTest2__Entity__) */
