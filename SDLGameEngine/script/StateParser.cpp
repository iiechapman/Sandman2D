
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
#include "SoundManager.h"
#include "Game.h"
#include "GameObjectFactory.h"



//TODO: need to remove old state parser code, and move to loadState()
//Old state parser, used to actually load scenes
bool StateParser::parseState(const char* stateFile,
                             string stateID, vector<IGameObject *>* pObjects,
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
    
    
    //Find and parse sounds
    //TiXmlElement* pSoundRoot = findElement(string("SOUNDS"), pStateRoot);
    
    //Find and parse songs
    //TiXmlElement* pSongRoot = findElement(string("SONGS"), pStateRoot);
    
    //Find and parse elements
    //TiXmlElement* pElementRoot = findElement(string("ELEMENTS"), pStateRoot);
    
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

//TODO Make generic to use any state
//New state parser, used to load levels
bool StateParser::loadState(const char* stateFile, PlayState* newState){
    
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
    TiXmlElement* pStateRoot = findElement(newState->getStateID(), pRoot);
    
    
    //Parse library for all assets
    
    //Find texture root and parse
    TiXmlElement* pTextureRoot = findElement(string("TEXTURES"), pStateRoot);
    parseTextures(pTextureRoot, newState->getTextureList());
    
    
    //Find and parse sounds
    TiXmlElement* pSoundRoot = findElement(string("SOUNDS"), pStateRoot);
    parseSounds(pSoundRoot, newState);
    
    //Find and parse songs
    TiXmlElement* pSongRoot = findElement(string("SONGS"), pStateRoot);
    parseSongs(pSongRoot, newState);
    
    //Find and parse elements
    TiXmlElement* pElementRoot = findElement(string("ELEMENTS"), pStateRoot);
    parseElements(pElementRoot, newState);
    
    
    //Find object root parse
    TiXmlElement* pObjectRoot = findElement(string("OBJECTS"), pStateRoot);
    parseObjects(pObjectRoot, newState->getGameObjects());
    
    //Find Level Root and parse
    TiXmlElement* pLevelRoot = findElement(string("LEVELS"), pStateRoot);

    if (pLevelRoot){
        parseLevels(pLevelRoot, newState->getLevelFiles());
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
        cout << "Error: State Root Null, or no Textures\n";
    }
    
}

void StateParser::parseLevels(TiXmlElement* pStateRoot,
                             map<string,string>* pLevelFiles){
    //TODO Add Error handling
    for (TiXmlElement* e = pStateRoot->FirstChildElement();
         e != NULL; e = e->NextSiblingElement()){
        string fileNameAttribute = e->Attribute("filename");
        string idAttribute = e->Attribute("ID");
        
        (*pLevelFiles)[idAttribute] = fileNameAttribute;
    }
    
}


void StateParser::parseObjects(TiXmlElement *pStateRoot, vector<IGameObject *> *pObjects){
    
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
            
            IGameObject* pGameObject  =
            GameObjectFactory::Instance()->create(e->Attribute("type"));
            
            pGameObject->load(*params);
            
            pGameObject->GetParams().printOut();
            
            pObjects->push_back(pGameObject);
            
        }
    } else {
        cout << "Object Root Null or no objects\n";
    }
}



TiXmlElement* StateParser::findElement(string element,TiXmlElement* root){
    for (TiXmlElement* e = root->FirstChildElement() ;
         e!= NULL; e = e->NextSiblingElement()){
        if (e->Value() == element ){
            cout << "Found \"" << element << "\" root!\n";
            return e;
        }
    }
    return 0;
}


    //TODO Add Error handling
void StateParser::parseSongs(TiXmlElement *pStateRoot, PlayState *currentState){

    for (TiXmlElement* e = pStateRoot->FirstChildElement();
         e != NULL; e = e->NextSiblingElement()){
        string fileName = "";
        string songID =  "";
        
        fileName = e->Attribute("filename");
        songID   = e->Attribute("ID");
        
        SoundManager::Instance()->loadSong(fileName, songID);
    }
}
    //TODO Add Error handling
void StateParser::parseSounds(TiXmlElement *pStateRoot, PlayState *currentState){
    for (TiXmlElement* e = pStateRoot->FirstChildElement();
         e != NULL; e = e->NextSiblingElement()){
        string fileName = "";
        string soundID =  "";
        
        fileName = e->Attribute("filename");
        soundID   = e->Attribute("ID");
        
        SoundManager::Instance()->loadSound(fileName, soundID);
    }
}

/*
 ====================
 StateParser::parseElements
 ====================
 */
///<Loads all elements from library file, injects them into new object state
void StateParser::parseElements(TiXmlElement *pStateRoot, PlayState *currentState){
    //Load up prototype elements for later use in map loading
    for (TiXmlElement* e = pStateRoot->FirstChildElement();
         e != NULL; e = e->NextSiblingElement()){
        GameObjectParams* params = new GameObjectParams();
        
        //Setup local values to hold state
        string name = "";
        string textureID = "";
        string ai = "";
        int GID = -1;
        string type = "";
        int row = 0;
        int numFrames = 0;
        int frame = 0;
        int animSpeed = 0;
        int width = 0;
        int height = 0;
        double x = 0;
        double y = 0;
        double scale = 1;
        
        SDL_Color color;
        SDL_BlendMode blendMode;
        
        color.r = 255;
        color.g = 255;
        color.b = 255;
        color.a = 255;
        blendMode = SDL_BLENDMODE_BLEND;
        
        //Load attributes from XML
        e->Attribute("GID",&GID);
        e->Attribute("row",&row);
        e->Attribute("frame",&frame);
        e->Attribute("width",&width);
        e->Attribute("height",&height);
        e->Attribute("numFrames",&numFrames);
        e->Attribute("animSpeed",&animSpeed);
        e->Attribute("scale",&scale);
        
        name = e->Attribute("name");
        type = e->Attribute("type");
        textureID = e->Attribute("textureID");
        
        if (e->Attribute("ai")){
            ai = e->Attribute("ai");
            
            if (ai == string("true")){
                params->setAI(true);
            } else {
                params->setAI(false);
            }
        }
        
        //Set object parameters with values loaded in from XML
        params->setName(name);
        params->setMaxFrames(numFrames);
        params->getPosition().setX(x);
        params->getPosition().setY(y);
        params->setScale(scale);
        params->setWidth(width);
        params->setHeight(height);
        params->setType(type);
        params->setRow(row);
        params->setFrame(frame);
        params->setStartFrame(frame);
        params->setAnimSpeed(animSpeed);
        params->setColor(color);
        params->setBlendMode(blendMode);
        params->setTextureID(textureID);
        
        
        (*currentState->getElements())[name] = params;
    }
}












































//END