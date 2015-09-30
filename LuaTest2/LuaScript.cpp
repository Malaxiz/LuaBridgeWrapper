//
//  LuaScript.cpp
//  LuaTest2
//
//  Created by Didrik Munther on 30/09/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include "LuaScript.h"

LuaScript::LuaScript(lua_State* L, std::string scriptName) :
_L(L), _scriptName(scriptName) {
}

LuaScript::~LuaScript() {
    auto i = _references.begin();
    while(i != _references.end()) {
        delete i->second;
        _references.erase(i++->first);
    }
    _references.clear();
}

void LuaScript::doFile() {
    luaL_dofile(_L, _scriptName.c_str());
}

LuaReference* LuaScript::getReference(std::string ref) {
    return _references[ref];
}

//template <class MemFn>
//void LuaScript::registerFunction(std::string ref, MemFn funcPtr) {
//    getGlobalNamespace(L).addFunction(ref.c_str(), funcPtr);
//}