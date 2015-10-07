//
//  Value.h
//  LuaTest2
//
//  Created by Didrik Munther on 07/10/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#ifndef __LuaTest2__Value__
#define __LuaTest2__Value__

#include <stdio.h>
#include <string>

#include "LuaScript.h"
#include "LuaReference.h"
#include "ComponentScript.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


class Value {
    
    enum Values {
        INT = 0,
        DOUBLE,
        STRING,
        BOOL
    };
    
public:
    Value(lua_State* L, int i) {
        if(lua_isboolean(L, i))
            init(lua_toboolean(L, i));
        else if(lua_isnumber(L, i))
            init(lua_tonumber(L, i));
        else if(lua_isstring(L, i))
            init(lua_tostring(L, i));
    }
    
    void init(std::string s) {
        stringValue = s;
        value = Values::STRING;
    }
    
    void init(double d) {
        if(static_cast<int>(d) == d) {
            intValue = (int)d;
            value = Values::INT;
        } else {
            doubleValue = (double)d;
            value = Values::DOUBLE;
        }
        
    }
    
    void init(int b) {
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

#endif /* defined(__LuaTest2__Value__) */
