//
//  StateParser.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/17/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__StateParser__
#define __SDLGameDevelopmentChapter1__StateParser__

#include <iostream>
#include <vector>
#include <map>
#include "tinyxml.h"
#include "PlayState.h"

using namespace std;

class GameObject;

class StateParser{
public:
    
    bool parseState( const char* stateFile,
                    string stateID, vector<GameObject*>* pObjects,
                    vector<string>* pTextureIDs, map<string,string>* pLevelFiles);
    
    bool loadState(const char* stateFile, PlayState* newState);
    
private:
    void parseObjects(TiXmlElement* pStateRoot,
                      vector<GameObject*>* pObjects);
    
    void parseTextures(TiXmlElement* pStateRoot,
                       vector<string>* pTextureIDs);
    
    void parseLevels(TiXmlElement* pStateRoot, map<string,string>* pLevelFiles);
    
    void parseSounds(TiXmlElement* pStateRoot ,PlayState* currentState);
    void parseSongs(TiXmlElement* pStateRoot, PlayState* currentState);
    void parseElements(TiXmlElement* pStateRoot, PlayState* currentState);
    
    
    TiXmlElement* findElement(string element,TiXmlElement* root);
    
    
};




#endif /* defined(__SDLGameDevelopmentChapter1__StateParser__) */
