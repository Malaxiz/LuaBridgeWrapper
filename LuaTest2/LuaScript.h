//
//  LuaScript.h
//  LuaTest2
//
//  Created by Didrik Munther on 30/09/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#ifndef __LuaTest2__LuaScript__
#define __LuaTest2__LuaScript__

#include <stdio.h>
#include <string>
#include <map>

extern "C" {
# include "lua/lua.h"
# include "lua/lauxlib.h"
# include "lua/lualib.h"
}

#include "LuaBridge/LuaBridge.h"

#include "LuaReference.h"


class LuaScript {
    
public:
    LuaScript(lua_State* L, std::string scriptName);
    ~LuaScript();
    
    void doFile() { luaL_dofile(_L, _scriptName.c_str()); }
    
    template<typename ... A>
    LuaReference* registerReference(A ... args) {
        LuaReference* ref = new LuaReference(getLuaState(), std::forward<A>(args) ...);
        _references[ref->getName()] = ref;
        return ref;
    }
    
    LuaReference* getReference(std::string ref);
    
    luabridge::Namespace getNamespace() {
        return luabridge::getGlobalNamespace(_L);
    }
    
    lua_State* getLuaState() {
        return _L;
    }
    
private:
    lua_State* _L;
    std::map<std::string, LuaReference*> _references;
    
    std::string _scriptName;
    
};

#endif /* defined(__LuaTest2__LuaScript__) */
