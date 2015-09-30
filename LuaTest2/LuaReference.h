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

extern "C" {
# include "lua/lua.h"
# include "lua/lauxlib.h"
# include "lua/lualib.h"
}

#include "LuaBridge/LuaBridge.h"


class LuaReference {
    
public:
//    LuaReference(lua_State* L, std::string name) :
//    luaRef(L, luabridge::getGlobal(L, name.c_str())), _name(name) {  }
//    
//    LuaReference(lua_State* L, LuaReference* reference, std::string name) :
//    luaRef(reference->getRefFromParent(reference->luaRef, name)), _name(name) {  }
    
    template<typename ... A>
    LuaReference(lua_State* L, A ... args) :
        luaRef(init(L, std::forward<A>(args) ...)) {

    }
    
//    luabridge::LuaRef getRefFromParent(luabridge::LuaRef ref, std::string name) {
//        return ref[name];
//    }
    
    // =========================================================
    
    template<typename T>
    luabridge::LuaRef init(lua_State* L, T head) {
        _name = head;
        return luabridge::getGlobal(L, head);
    }
    
    template<typename T, typename ... A>
    luabridge::LuaRef init(lua_State* L, T head, A ... args) {
        luabridge::LuaRef ref = luabridge::getGlobal(L, head);
        return _init(ref, std::forward<A>(args) ...);
    }
    
    template<typename T>
    luabridge::LuaRef _init(luabridge::LuaRef parent, T head) {
        _name = head;
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
    
};

#endif /* defined(__LuaTest2__LuaReference__) */
