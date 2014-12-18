//
//  ScriptHandler.cpp
//  SDLGameEngine
//
//  Created by Evan Chapman on 12/15/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include <iostream>

#include "ScriptHandler.h"

#include "lua.hpp"
extern "C"{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

using namespace std;

ScriptHandler::ScriptHandler(){
  
}

ScriptHandler::~ScriptHandler(){
  
}


void ScriptHandler::CallFunction(const char *function){
  lua_getglobal(m_State, function);
  if (lua_pcall(m_State, 0, 0, 0) !=0){
    ReportError();
  }
}

void ScriptHandler::SendValue(int value, const char* valueName){
  lua_pushnumber(m_State, value);
  lua_setglobal(m_State, valueName);
}

//initializes the Lua environment
void ScriptHandler::Init(){
  m_State = luaL_newstate();
  
  if (m_State){
    luaL_openlibs(m_State);
  } else {
    ReportError();
  }
}

//loads a script and executes it
void ScriptHandler::Load(){
  cout << "Running script..\n";
  if (luaL_dofile(m_State, "res/lib/scr/test.lua") !=0){
    ReportError();
  }
}

//Prints out lua error if one occurs
void ScriptHandler::ReportError(){
  cout << "Lua Error..\n";
  cerr << "-- " << lua_tostring(m_State, -1) << std::endl;
  lua_pop(m_State, 1); // remove error message
}

//cleans up lua environment
void ScriptHandler::Close(){
  lua_close(m_State);
}









