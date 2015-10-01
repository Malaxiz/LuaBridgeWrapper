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
        return references.find(ref) != references.end();
    }
    
private:
    std::map<std::string, LuaReference*> references;
    
//    LuaReference* onLoopFunc;
//    LuaReference* onSerializeFunc;
//    LuaReference* onInitFunc;
    
    rapidjson::Document variables;
    
};

#endif /* defined(__LuaTest2__Entity__) */
