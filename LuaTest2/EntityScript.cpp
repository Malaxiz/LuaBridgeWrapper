//
//  EntityScript.cpp
//  LuaTest2
//
//  Created by Didrik Munther on 01/10/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include "EntityScript.h"


EntityScript::EntityScript(LuaScript* script) : script(script) {
    
    script->registerReference("game", "object");
    object = script->getReference("game.object")->cast<std::string>();
    script->registerReference(object.c_str());
    
    script->registerReference("game", "references")->luaRef.push(script->getLuaState());
    push(script->getLuaState(), luabridge::Nil ());
    while (lua_next(script->getLuaState(), -2))
    {
        luabridge::LuaRef key = luabridge::LuaRef::fromStack(script->getLuaState(), -2);
        luabridge::LuaRef val = luabridge::LuaRef::fromStack(script->getLuaState(), -1);
        
        std::string value = val.cast<std::string>();
        _references.push_back(value);
        
        script->registerReference(script->getReference("game.object")->cast<std::string>().c_str(), value.c_str());
        
        lua_pop(script->getLuaState(), 1);
    }
    
    
    
}