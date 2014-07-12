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
#include "tinyxml.h"


using namespace std;

class GameObject;

class StateParser{
public:
    
    bool parseState( const char* stateFile,
                    string stateID, vector<GameObject*>* pObjects,
                    vector<string>* pTextureIDs, string* pLevelFile);
    
private:
    void parseObjects(TiXmlElement* pStateRoot,
                      vector<GameObject*>* pObjects);
    
    void parseTextures(TiXmlElement* pStateRoot,
                       vector<string>* pTextureIDs);
    
    void parseLevel(TiXmlElement* pStateRoot,string* pLevelFile);
    
    
};




#endif /* defined(__SDLGameDevelopmentChapter1__StateParser__) */
