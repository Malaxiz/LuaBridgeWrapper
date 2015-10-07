//
//  Component.h
//  LuaTest2
//
//  Created by Didrik Munther on 07/10/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#ifndef __LuaTest2__Component__
#define __LuaTest2__Component__

#include <stdio.h>

#include "ComponentScript.h"
#include "LuaReference.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


class Entity;

class Component {
    
public:
    Component(ComponentScript* script, Entity* parent);
    
    void onInit();
    void onLoop();
    void onSerialize(rapidjson::Value* v, rapidjson::Document::AllocatorType* alloc);
    
    void addMember(std::string key, std::string value);
    
    // ===========================================
    
    rapidjson::Value* getJsonValue(std::string key);
    
    int setVariable(lua_State* L);
    int getVariable(lua_State* L);
    
    // ===========================================
    
    Entity* getParent() {
        return parent;
    }
    
private:
    Entity* parent;
    
    ComponentScript* script;
    rapidjson::Document variables;
    
    rapidjson::Value* tempV; // Temporary when serializing
    rapidjson::Document::AllocatorType* tempAlloc;
    
};

#endif /* defined(__LuaTest2__Component__) */
