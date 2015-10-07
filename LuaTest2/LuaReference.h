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
#include <vector>

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
        luaRef(init(L, std::forward<A>(args) ...)),
        L(L), currentArgc(0), openCall(false) {
        _name = strdup(addToName(std::forward<A>(args) ...).str().c_str());
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
    lua_State* L;
    
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
    
    // --------------------------------------------------------------
    
    int currentArgc;
    bool openCall;
    
    void beginCall() {
        if(openCall)
            std::cout << "[ERROR] /* Call opening before closing old one in reference " << getName() << " */\n";
        
        luaRef.beginCall();
        openCall = true;
    }
    
    luabridge::LuaRef const endCall() {
        if(!openCall)
            std::cout << "[ERROR] /* Call closed before opening one in reference " << getName() << " */\n";
        
        int argc = currentArgc;
        currentArgc = 0;
        openCall = false;
        return luaRef.endCall(argc);
    }
    
    template<class T>
    void addArgument(T t) {
        luaRef.addArgument(t);
        currentArgc += 1;
    }
    
    // --------------------------------------------------------------
    
private:
    const char* _name;
    std::vector<const char*> _referenceName;
    
    template<typename T>
    std::stringstream addToName(T head) {
        return std::stringstream(head);
    }
    
    template<typename T, typename ... A>
    std::stringstream addToName(T head, A ... args) {
        _referenceName.push_back(head);
        
        std::stringstream s;
        s << head << ".";
        s << addToName(std::forward<A>(args) ...).str();
        return s;
    }
    
};

#endif /* defined(__LuaTest2__LuaReference__) */
