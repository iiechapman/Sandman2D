//
//  main.cpp
//  LuaTest
//
//  Created by Evan Chapman on 10/31/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "lua.hpp"

using namespace std;

// Lua Function Declarations
//string PrintWorkingDirectory();
void error(lua_State *L, const char* fmt, ...);
void load(lua_State *L ,const char* file , int *width , int *height);

double functionTest(lua_State *L , double x, double y);

//Helper Functions
string PrintWorkingDirectory();



int luatest(int argc, const char * argv[]) {
    cout << "Welcome to the Lua Console!\n";
    
    //Create Lua state and environmental variables
    char buff[256];
    int error;
    lua_State *L = luaL_newstate(); //Lua State
    luaL_openlibs(L);
    
    
    //test loading from file
    int width   = 0;
    int height  = 0;
    
    //Grab current directory, add file name to end of it for local file
    string currentDirectory = PrintWorkingDirectory() + "/config.lua";
    const char* currentFile = currentDirectory.c_str();
    
    load(L, currentFile, &width, &height);
    
    //Test loading from string
    cout << "Testing string function:\n";
    string functionString = "print(\"functionCall\")";
    const char* functionCall = functionString.c_str();
    error = luaL_loadstring(L, functionCall) || lua_pcall(L, 0, 0, 0);
    
    //Check Stack for size
    int sizeRequest = 10;
    int stackRequestGranted = lua_checkstack(L, sizeRequest);
    cout << "Was stack resized? " << stackRequestGranted << "\n";
    
    //    //Push object on stack
    //    printf("Adding new stack value\n");
    //    lua_pushnumber(L, lua_Number(10));
    
    
    //Loop while receiving Lua commands
    while (L) {
        cout << "LuaConsole:$ ";
        fgets(buff, sizeof(buff), stdin);
        int topOfStack = lua_gettop(L);
        
        cout << "Current Stack Size: " << topOfStack << "\n";
        
        error = luaL_loadstring(L, buff);
        cout << "Checking LuaType: " << lua_type(L, -1) << "\n";
        
        switch (lua_type(L, -1)) {
                
            case LUA_TNIL:
                cout << "Type is NIL value\n";
                break;
                
            case LUA_TBOOLEAN:
                cout << "Type is boolean\n";
                printf(lua_toboolean(L, topOfStack) ? "true\n" : "false\n");
                break;
                
            case LUA_TNUMBER:
                cout << "Type is number\n";
                break;
                
            case LUA_TSTRING:
                cout << "Type is string\n";
                printf("%s" , lua_tostring(L, topOfStack));
                break;
                
            case LUA_TTABLE:
                cout << "Type is table\n";
                break;
                
            case LUA_TFUNCTION:
                cout << "Type is function\n";
                break;
                
            case LUA_TUSERDATA:
                cout << "Type is userdata\n";
                break;
                
                
            default:
                //error(L,"Type not identified");
                
                break;
        }
        
        //Run element on lua stack
        error = lua_pcall(L, 0, 0, 0);
        
        if (error){
            fprintf(stderr, "Error: %s\n", lua_tostring(L, -1));
            lua_pop(L, 1); //pop error from stack
        } else {
            cout << "Accepted command.\n";
        }
    }
    
    
    lua_close(L);
    return 0;
}


void error(lua_State *L, const char* fmt, ...){
    va_list argp; //Create variadic argument list
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    lua_close(L);
    exit(EXIT_FAILURE);
}

//Test loading lua files
void load(lua_State *L ,const char* file , int *width , int *height){
    if (luaL_loadfile(L, file) || lua_pcall(L, 0, 0, 0)) {
        error(L, "Error loading file:%s, %s\n",file,lua_tostring(L, -1));
        
    } else {
        printf("Sucessful loading of file:%s\n",file);
        
        lua_getglobal(L, "width");
        lua_getglobal(L, "height");
        
        if(!lua_isnumber(L, -2)){
            error(L, "width should be a number\n");
        }
        
        if(!lua_isnumber(L, -1)){
            error(L, "height should be a number\n");
        }
        
        *width = int(lua_tointeger(L, -2));
        *height = int(lua_tointeger(L, -1));
        
        cout << "Width: " << *width << "\n";
        cout << "Height: " << *height << "\n";
    }
}


double functionTest(lua_State *L , double x, double y){
    int isNum = 0;
    double z = 0.0;
    
    //Push function and arguments
    lua_getglobal(L, "functionCall");//Function pushed
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    
    //Call the function
    if (lua_pcall(L, 2, 1, 0) != LUA_OK){
        error(L, "Error running function, %s\n", lua_tostring(L, -1));
    }
    
    //Retrieve result from function
    z = lua_tonumberx(L, -1, &isNum);
    if (!isNum){
        error(L, "Function must return number\n");
    }
    
    lua_pop(L, 1);
    
    return z;
}


////Prints current directory app is executed from
//string PrintWorkingDirectory(){
//    char filenameMax[FILENAME_MAX];
//    getcwd(filenameMax, sizeof(filenameMax));
//    cout << "Current working directory:\n" << filenameMax << "\n";
//    return string(filenameMax);
//}












