
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

/*
 Parses the library XML file for state
 
 Pass in stateID string and it looks for that state to load
 
 */

bool StateParser::parseState(const char* stateFile,
                             string stateID, vector<GameObject *>* pObjects,
                             vector<string>* pTextureIDs, map<string,string>* pLevelFiles){
    
    
    //Create an XML document
    TiXmlDocument xmlDoc;
    
    //Load the XML file
    cout << "Loading XML file\n";
    if (! xmlDoc.LoadFile(stateFile)){
        cout << "XML ERROR-\n";
        cout << xmlDoc.ErrorDesc() << endl;
        return false;
    }
    

    //Find root element
    TiXmlElement* pRoot = xmlDoc.RootElement();
    
    //Find state root
    TiXmlElement* pStateRoot = findElement(stateID, pRoot);

    
    //Parse library for all assets
    
    //Find texture root and parse
    TiXmlElement* pTextureRoot = findElement(string("TEXTURES"), pStateRoot);
    parseTextures(pTextureRoot, pTextureIDs);
    
    //TODO: add song,sound and element parsing here
    
    //Find object root parse
    TiXmlElement* pObjectRoot = findElement(string("OBJECTS"), pStateRoot);
    parseObjects(pObjectRoot, pObjects);
    
    //Find Level Root and parse
    TiXmlElement* pLevelRoot = findElement(string("LEVELS"), pStateRoot);
    cout << "Searching for Level Root\n";
    
    //Parse Level and create
    if (pLevelRoot){
        parseLevels(pLevelRoot, pLevelFiles);
    } else {
        cout << "No levels in this state\n";
    }
    
    return true;
}



void StateParser::parseTextures(TiXmlElement* pStateRoot,
                                vector<string>* pTextureIDs){
    
    if (pStateRoot){
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
    } else {
        cout << "Error: State Root Null\n";
    }
    
}

void StateParser::parseLevels(TiXmlElement* pStateRoot,
                             map<string,string>* pLevelFiles){
    
    for (TiXmlElement* e = pStateRoot->FirstChildElement();
         e != NULL; e = e->NextSiblingElement()){
        string fileNameAttribute = e->Attribute("filename");
        string idAttribute = e->Attribute("ID");
        
        (*pLevelFiles)[idAttribute] = fileNameAttribute;
    }
    
}


void StateParser::parseObjects(TiXmlElement *pStateRoot, vector<GameObject *> *pObjects){
    
    if (pStateRoot){
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
            
            params->setX(x);
            params->setY(y);
            params->setWidth(width);
            params->setHeight(height);
            params->setMaxFrames(numFrames);
            params->setAnimSpeed(animSpeed);
            params->setTextureID(textureID);
            params->setCallBackID(callBackID);
            
            GameObject* pGameObject  =
            GameObjectFactory::Instance()->create(e->Attribute("type"));
            
            pGameObject->load(*params);
            
            pGameObject->GetParams().printOut();
            
            pObjects->push_back(pGameObject);
            
        }
    } else {
        cout << "State Root Null\n";
    }
}



TiXmlElement* StateParser::findElement(string element,TiXmlElement* root){
    for (TiXmlElement* e = root->FirstChildElement() ;
         e!= NULL; e = e->NextSiblingElement()){
        if (e->Value() == element ){
            cout << "Found " << element << " root!\n";
            return e;
        }
    }
    return 0;
}






























































//END