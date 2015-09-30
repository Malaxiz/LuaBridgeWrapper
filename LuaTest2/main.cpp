//
//  main.cpp
//  LuaTest2
//
//  Created by Didrik Munther on 29/09/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include <iostream>

#include "LuaScript.h"
#include "LuaReference.h"

#include "Entity.h"


LuaScript talkable("Talkable.lua");
LuaScript hurtable("Hurtable.lua");

std::string printMessage(const std::string s) {
    std::cout << s << std::endl;
    return "returned";
}

int getValue() {
    return hurtable.getReference("y")->cast<int>();
}

int main(int argc, const char* argv[]) {
    
//    LuaScript luaScript("script.lua");
//    
//    luaScript.getNamespace().
//        beginNamespace("game").
//            addFunction("printMessage", printMessage).
//        endNamespace();
//    
//    luaScript.doFile();
//    
//    
//    luaScript.registerReference("test", "sumNumbers");
//    luaScript.registerReference("test", "testString");
//    luaScript.registerReference("test", "testNumber");
//    luaScript.registerReference("test", "testFunction");
//    luaScript.registerReference("test", "asdf", "bla", "var");
//    
//    std::cout << "SumNumbers: " << luaScript.getReference("test.sumNumbers")->call(5, 6) << "\n";
//    std::cout << "TestString: " << luaScript.getReference("test.testString")->cast<std::string>() << "\n";
//    std::cout << "TestNumber: " << luaScript.getReference("test.testNumber")->cast<int>() << "\n";
//    std::cout << "TestFunction: "; luaScript.getReference("test.testFunction")->call();
//    std::cout << "Nested variable: " << luaScript.getReference("test.asdf.bla.var")->cast<std::string>() << "\n";
    
    
//    talkable.getNamespace().
//        beginNamespace("game").
//            addFunction("getValue", getValue).
//        endNamespace();
//    
//    talkable.doFile();
//    hurtable.doFile();
//    
//    hurtable.registerReference("y");
//    talkable.registerReference("myFunc");
//    
//    talkable.getReference("myFunc")->call();
    
    Entity myEntity;
    myEntity.init("Player.lua", "player");
    
    Entity myEntity2;
    myEntity2.init("Player.lua", "player2");
    
    myEntity.onLoop(&myEntity2);
    
    
    
}
