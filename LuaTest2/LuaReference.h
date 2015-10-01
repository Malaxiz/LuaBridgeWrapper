//
//  LuaReference.h
//  LuaTest2
//
//  Created by Didrik Munther on 30/09/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#ifndef __LuaTest2__LuaReference__
#define __LuaTest2__LuaReference__

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>

extern "C" {
# include "lua/lua.h"
# include "lua/lauxlib.h"
# include "lua/lualib.h"
}

#include "LuaBridge/LuaBridge.h"


class LuaReference {
    
public:
    template<typename ... A>
    LuaReference(lua_State* L, A ... args) :
        luaRef(init(L, std::forward<A>(args) ...)) {
        _name = strdup(addToName(std::forward<A>(args) ...).str().c_str());
        //std::cout << _name << "\n";
        
    }
    
    // ========================== init ==============================
    
    template<typename T>
    luabridge::LuaRef init(lua_State* L, T head) {
        return luabridge::getGlobal(L, head);
    }
    
    template<typename T, typename ... A>
    luabridge::LuaRef init(lua_State* L, T head, A ... tail) {
        luabridge::LuaRef ref = luabridge::getGlobal(L, head);
        return _init(ref, std::forward<A>(tail) ...);
    }
    
    template<typename T>
    luabridge::LuaRef _init(luabridge::LuaRef parent, T head) {
        return parent[head];
    }
    
    template<typename T, typename ... A>
    luabridge::LuaRef _init(luabridge::LuaRef parent, T head, A ... tail) {
        return _init(parent[head], std::forward<A>(tail) ...);
    }
    
    // ==============================================================
    
    luabridge::LuaRef luaRef;
    
    template<typename ... A>
    luabridge::LuaRef call(A ... args) {
        return luaRef(std::forward<A>(args) ...);
    }
    
    template<typename T>
    T cast() {
        return luaRef.cast<T>();
    }
    
    const char* getName() {
        return _name;
    }
    
private:
    const char* _name;
    
    template<typename T>
    std::stringstream addToName(T head) {
        return std::stringstream(head);
    }
    
    template<typename T, typename ... A>
    std::stringstream addToName(T head, A ... args) {
        std::stringstream s;
        s << head << ".";
        s << addToName(std::forward<A>(args) ...).str();
        return s;
    }
    
};

#endif /* defined(__LuaTest2__LuaReference__) */
