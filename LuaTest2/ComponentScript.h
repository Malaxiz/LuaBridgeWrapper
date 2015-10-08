//
//  ComponentScript.h
//  LuaTest2
//
//  Created by Didrik Munther on 01/10/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#ifndef __LuaTest2__ComponentScript__
#define __LuaTest2__ComponentScript__

#include <stdio.h>
#include <map>

#include "LuaScript.h"
#include "LuaReference.h"


class ComponentScript {
    
public:
    ComponentScript(LuaScript* script);
    
    LuaScript* script;
    
    std::string object;
    
    bool hasReference(std::string ref) {
        return references.find(ref) != references.end();
    }
    
    LuaReference* getReference(std::string ref) {
        if(hasReference(ref))
            return references[ref];
        else
            return nullptr;
    }
    
    std::map<std::string, LuaReference*> references;
    
};

#endif /* defined(__LuaTest2__ComponentScript__) */
