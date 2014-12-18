//
//  ScriptHandler.h
//  SDLGameEngine
//
//  Created by Evan Chapman on 12/15/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameEngine__ScriptHandler__
#define __SDLGameEngine__ScriptHandler__

#include <stdio.h>

#include "lua.hpp"

extern "C"{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class ScriptHandler{
public:
  ScriptHandler();
  ~ScriptHandler();
  
  void Init();
  void Load();
  void Close();
  void SendValue(int value, const char* valueName);
  void CallFunction(const char* function);
  void ReportError();
  
  
private:
  lua_State* m_State;
  
};


#endif /* defined(__SDLGameEngine__ScriptHandler__) */
