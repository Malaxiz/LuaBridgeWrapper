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
#include "EntityScript.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


class Entity {
    
public:
    Entity();
    
    void init(EntityScript* script);
    
    void onLoop(Entity* other);
    
    std::string onSerialize();
    
    // ================ Getters and setters ============== //
    
    void setStringVariable(std::string key, std::string value) {
        getVariable(key)->SetString(value.c_str(), (int)value.length(), variables.GetAllocator());
    }
    
    void setIntVariable(std::string key, int value) {
        getVariable(key)->SetInt(value);
    }
    
    std::string getStringVariable(std::string key) {
        if(!getVariable(key)) {
            std::cout << "WARNING: Variable not found: " << key << "\n";
            return "";
        }
            
        return getVariable(key)->GetString();
    }
    
    int getIntVariable(std::string key) {
        if(!getVariable(key)) {
            std::cout << "WARNING: Variable not found: " << key << "\n";
            return 0;
        }
        
        return getVariable(key)->GetInt();
    }
    
    LuaReference* getReference(std::string key) {
        if(hasReference(key))
            return (*references)[key];
        else
            return nullptr;
    }
    
    rapidjson::Value* getVariable(std::string key) {
        if(variables.HasMember(key.c_str())) {
            auto keyValue = rapidjson::Value(key.c_str(), variables.GetAllocator());
            return &variables[keyValue];
        }
        else
            return nullptr;
    }
    
    
    
    // =================================================== //
    
    void say(std::string phrase) { std::cout << phrase << "\n"; }
    
    bool hasReference(std::string ref) {
        return references->find(ref) != references->end();
    }
    
    // ---------------------------------------------------- //
    
    int callScriptFunction(lua_State* L) {
//        //std::string script = lua_tostring(L, 1);
//        //std::string function = lua_tostring(L, 2);
//        
//        std::cout << "test\n";
//        
//        return 1;
        
        int argc = lua_gettop(L);
        
        for(int i = 2; i <= argc; i++) { // remember to start iterating from 2
            std::cout << "Variable: " << lua_tostring(L, i) << ", is number: " << lua_isnumber(L, i) << "\n";
        }
        
        lua_pushstring(L, "String returned from C++");
        
        return 1;
    }
    
private:
    std::map<std::string, LuaReference*>* references;
    
//    LuaReference* onLoopFunc;
//    LuaReference* onSerializeFunc;
//    LuaReference* onInitFunc;
    
    rapidjson::Document variables;
    
};

#endif /* defined(__LuaTest2__Entity__) */
