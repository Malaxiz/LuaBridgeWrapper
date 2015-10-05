//
//  main.cpp
//  LuaTest2
//
//  Created by Didrik Munther on 29/09/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include <iostream>
#include <vector>


#include "LuaScript.h"
#include "LuaReference.h"
#include "EntityScript.h"

#include "Entity.h"


lua_State* L = luaL_newstate();

class Value {
    
    enum Values {
        INT = 0,
        DOUBLE,
        STRING,
        BOOL
    };
    
public:
    Value(std::string s) {
        stringValue = s;
        value = Values::STRING;
    }
    
    Value(double d) {
        if(static_cast<int>(d) == d) {
            intValue = (int)d;
            value = Values::INT;
        } else {
            doubleValue = (double)d;
            value = Values::DOUBLE;
        }
        
    }
    
    Value(int b) {
        boolValue = (bool)b;
        value = Values::BOOL;
    }
    
    void pushValue(lua_State* L) {
        switch (value) {
            case Values::STRING:
                lua_pushstring(L, stringValue.c_str());
                break;
                
            case Values::INT:
                lua_pushnumber(L, intValue);
                break;
                
            case Value::DOUBLE:
                lua_pushnumber(L, doubleValue);
                break;
                
            case Values::BOOL:
                lua_pushnumber(L, boolValue);
                break;
                
            default:
                std::cout << "Error: values empty.\n";
                break;
        }
    }
    

    Values value;
private:
    
    std::string stringValue;
    int intValue;
    double doubleValue;
    bool boolValue;
    
};

int callLuaFunctionFromLua(lua_State* L) {
    
    int argc = lua_gettop(L);
    
    assert(lua_isuserdata(L, 1));
    
    std::vector<Value> values;
    for(int i = 1; i <= argc; i++) {
        if(lua_isboolean(L, i))
            values.push_back(Value(lua_toboolean(L, i)));
        else if(lua_isnumber(L, i))
            values.push_back(Value(lua_tonumber(L, i)));
        else if(lua_isstring(L, i))
            values.push_back(Value(lua_tostring(L, i)));
    }
    
    //LuaReference* reference = *((LuaReference**)lua_touserdata(L, 1));

    //lua_getglobal(L, reference->getName());
    
    
    
    return 1;
}

int main(int argc, const char* argv[]) {
    
    luaL_openlibs(L);
    
    luabridge::getGlobalNamespace(L)
//        .addCFunction("myFunc", &myFunc)
        .beginClass<Entity>("Entity")
            .addConstructor<void(*)(void)>()
            .addFunction("say", &Entity::say)
            .addFunction("getString", &Entity::getStringVariable)
            .addFunction("setString", &Entity::setStringVariable)
            .addFunction("getInt", &Entity::getIntVariable)
            .addFunction("setInt", &Entity::setIntVariable)
            .addFunction("getReference", &Entity::getReference)
            .addCFunction("callCFunction", &Entity::callScriptFunction)
        .endClass()
        .beginClass<LuaReference>("LuaReference")
            .addConstructor<void(*) (lua_State*, const char*)>()
        .endClass();
    
    //lua_register(L, "myFunc", myFunc);
    //lua_register(L, "test", Entity::callScriptFunction);
    
    // --
    
    LuaScript enemyLuaScript(L, "Enemy.lua");
    LuaScript entityLuaScript(L, "Player.lua");
    
    EntityScript entityScript(&entityLuaScript);
    EntityScript enemyScript(&enemyLuaScript);
    
    // --
    
    Entity myEntity;
    myEntity.init(&entityScript);
    
    Entity myEntity2;
    myEntity2.init(&enemyScript);
    
    while(myEntity.getIntVariable("health") > 0) { // Loop and let enemy attack player
        myEntity.onLoop(&myEntity2);
        myEntity2.onLoop(&myEntity);
    }
    
    //printMessage(myEntity.onSerialize());
    //printMessage(myEntity2.onSerialize()); // Will not run, because enemy does not have a seralize function
    
}
