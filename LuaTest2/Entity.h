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

#include "LuaScript.h"
#include "LuaReference.h"


class Entity {
    
public:
    Entity();
    ~Entity();
    
    void init(std::string scriptPath, std::string object);
    
    void onLoop(Entity* other);
    
    int getHealth() const { return health; }
    void setHealth(const int& value) { health = value; }
    int health;
    
    std::string getName() const { return name; }
    void setName(const std::string& value) { name = value; }
    std::string name;
    
    void say(std::string phrase) { std::cout << phrase << "\n"; }
    
private:
    LuaScript* script;
    
    LuaReference* onLoopFunc;
    
};

#endif /* defined(__LuaTest2__Entity__) */
