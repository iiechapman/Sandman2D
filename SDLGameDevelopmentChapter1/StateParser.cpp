
//
//  StateParser.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/17/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "StateParser.h"
#include "GameObjectParams.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"

bool StateParser::parseState(const char* stateFile,
                             string stateID, vector<GameObject *>* pObjects,
                             vector<string>* pTextureIDs, string* pLevelFile){
    
    
    //Create an XML document
    TiXmlDocument xmlDoc;
    
    //Load the XML file
    cout << "Loading XML file\n";
    if (! xmlDoc.LoadFile(stateFile)){
        cout << "XML ERROR-\n";
        cout << xmlDoc.ErrorDesc() << endl;
        return false;
    }
    
    
    //Get the root element
    TiXmlElement* pRoot = xmlDoc.RootElement();
    
    //Pre declare states root node
    TiXmlElement* pStateRoot = 0;
    
    //Find root node
    for (TiXmlElement* e = pRoot->FirstChildElement() ;
         e!= NULL; e = e->NextSiblingElement()){
        if (e->Value() == stateID ){
            pStateRoot = e;
            cout << "Found State Root\n";
        }
    }
    
    //Pre declare the texture root
    TiXmlElement* pTextureRoot = 0;
    
    //Find the texture root
    for (TiXmlElement* e = pStateRoot->FirstChildElement() ;
         e != NULL ; e = e->NextSiblingElement()){
        if (e->Value() == string("TEXTURES")){
            pTextureRoot = e;
            cout << "Found Texture Root\n";
        }
    }
    
    //Parse all textures
    parseTextures(pTextureRoot, pTextureIDs);
    
    
    //Pre declare object root node
    TiXmlElement* pObjectRoot = 0;
    
    //Find object root node
    for ( TiXmlElement* e = pStateRoot->FirstChildElement();
         e != NULL; e = e->NextSiblingElement()){
        if (e->Value() == string("OBJECTS")){
            pObjectRoot = e;
            cout << "Found Object Root\n";
        }
    }
    
    //Parse objects
    parseObjects(pObjectRoot, pObjects);
    
    
    //Pre declare object root node
    TiXmlElement* pLevelRoot = 0;
    cout << "Searching for Level Root\n";
    
    //Find object root node
    for ( TiXmlElement* e = pStateRoot->FirstChildElement();
         e != NULL; e = e->NextSiblingElement()){
        if (e->Value() == string("LEVEL")){
            pLevelRoot = e;
            cout << "Found Level Root\n";
            //Parse objects
            parseLevel(pLevelRoot, pLevelFile);
        }
    }
    
    return true;
}



void StateParser::parseTextures(TiXmlElement* pStateRoot,
                                vector<string>* pTextureIDs){
    
    for (TiXmlElement* e = pStateRoot->FirstChildElement();
         e != NULL; e = e->NextSiblingElement()){
        string fileNameAttribute = e->Attribute("filename");
        string idAttribute = e->Attribute("ID");
        
        cout << "Found Filename: " << fileNameAttribute << endl;
        cout << "Found ID: " << idAttribute << endl;
        
        
        pTextureIDs->push_back(idAttribute);
        
        TextureManager::Instance()->load
        (fileNameAttribute, idAttribute, Game::Instance()->getRenderer());
        
    }
    
}

void StateParser::parseLevel(TiXmlElement* pStateRoot,
                                string* pLevelFile){
    
    for (TiXmlElement* e = pStateRoot->FirstChildElement();
         e != NULL; e = e->NextSiblingElement()){
        string fileNameAttribute = e->Attribute("filename");
        string idAttribute = e->Attribute("ID");
        
        *pLevelFile = fileNameAttribute;
    }
    
}


void StateParser::parseObjects(TiXmlElement *pStateRoot, vector<GameObject *> *pObjects){
    
    for (TiXmlElement* e = pStateRoot->FirstChildElement();
         e != NULL; e = e->NextSiblingElement()){
        
        int x, y, width, height, numFrames,callBackID,animSpeed;
        string textureID, lockTo;
        GameObjectParams* params = new GameObjectParams();
        
        e->Attribute("x", &x);
        e->Attribute("y", &y);
        e->Attribute("width", &width);
        e->Attribute("height", &height);
        e->Attribute("numFrames", &numFrames);
        e->Attribute("callBackID", &callBackID);
        e->Attribute("animSpeed", &animSpeed);
        
        textureID = e->Attribute("textureID");
        
        //Check if object is locked to other object
        if (e->Attribute("lockTo")){
            lockTo = e->Attribute("lockTo");
            cout << "Locked game object to " << lockTo << endl;
        } else {
            lockTo = "NULL";
        }
        
        params->setX(x);
        params->setY(y);
        params->setWidth(width);
        params->setHeight(height);
        params->setMaxFrames(numFrames);
        params->setAnimSpeed(animSpeed);
        params->setTextureID(textureID);
        params->setCallBackID(callBackID);
        params->setLockTo(lockTo);
         
        GameObject* pGameObject  =
        GameObjectFactory::Instance()->create(e->Attribute("type"));
        
        pGameObject->load(*params);
        
        pGameObject->GetParams().printOut();
        
        pObjects->push_back(pGameObject);
        
    }
}


































































//END