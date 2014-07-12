//
//  LevelParser.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 6/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include <string>
#include <vector>
#include <zlib.h>
#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "base64.h"


Level* LevelParser::parseLevel(const char* levelFile){
    
    //Create the XML document and load from file
    TiXmlDocument levelDocument;
    levelDocument.LoadFile(levelFile);
    
    //Create the level object
    
    Level* pLevel = new Level();
    
    //Get the root node
    TiXmlElement* pRoot = levelDocument.RootElement();
    
    pRoot->Attribute("tilewidth", &m_tileSize);
    pRoot->Attribute("width" , &m_width);
    pRoot->Attribute("height", &m_height);
    //ToDo add orientation and version number
    
    //Parse the textures
    for (TiXmlElement* e = pRoot->FirstChildElement();
         e != NULL; e = e->NextSiblingElement()){
        cout << "Parsing for textures\n";
                if (e->Value() == string("properties")){
                    for (TiXmlElement* property = e->FirstChildElement();
                         property != NULL; property = property->NextSiblingElement()){
                        parseTextures(property);
                    }
                }
            }
    
    //parse the tilesets
    for (TiXmlElement* e = pRoot->FirstChildElement();
         e != NULL; e = e->NextSiblingElement()){
        if (e->Value() == string("tileset")){
            parseTilesets(e, pLevel->getTilesets());
        }
    }
    
    //Parse level layers
    for (TiXmlElement* e = pRoot->FirstChildElement();
         e != NULL ; e = e->NextSiblingElement()){
        if (e->Value() == string("layer") ||
            e->Value() == string("objectgroup")){
            string layerType = e->Attribute("name");
            
            if (e->FirstChildElement()->Value() == string("object")){
                //Parse Object layer
                parseObjectLayer(e, pLevel->getLayers(),layerType,pLevel);
            } else if (e->FirstChildElement()->Value() == string("properties")){
                //Parse Tile Layer
                parseTileLayer(e, pLevel->getLayers(),pLevel->getCollisionLayers(), pLevel->getTilesets());
            }
        }
    }
    
    return pLevel;
}

void LevelParser::parseLibrary(const char* levelFile){
    cout << "Loading library file\n";
    //    TextureManager::Instance()->load
    //(pTextureRoot->Attribute("value"),
    //pTextureRoot->Attribute("name"), Game::Instance()->getRenderer());
}

void LevelParser::parseTilesets(TiXmlElement *pTileSetRoot, vector<Tileset> *pTilesets){
    
    //Store element for parsing;
    
    TiXmlElement* image = pTileSetRoot->FirstChildElement();
    
    //Reformat file source
    string source = image->Attribute("source");
    string tempSource = "";
    string finalSource = "";
    
    for (int i = 0 ; i < source.size() ; i++){
        tempSource += source[i];
        
        if (source[i] == '/'){
            tempSource = "";
        }
        finalSource = "assets/tiles/" + tempSource;
    }
    
    cout << "Final Source -\n" << finalSource << endl;
    
    //Add tileset to texture manager
    TextureManager::Instance()->load
    (finalSource,pTileSetRoot->Attribute("name"), Game::Instance()->getRenderer());
    
    //Create tileset object
    Tileset tileset;
    image->Attribute("width",&tileset.width);
    image->Attribute("height",&tileset.height);
    
    pTileSetRoot->Attribute("firstgid", &tileset.firstGridID);
    pTileSetRoot->Attribute("tilewidth", &tileset.tileWidth);
    pTileSetRoot->Attribute("tileheight", &tileset.tileHeight);
    
    //Check if spacing or margin available
    if (pTileSetRoot->Attribute("spacing")){
        pTileSetRoot->Attribute("spacing", &tileset.spacing);
    } else {
        tileset.spacing = 0;
    }
    
    if (pTileSetRoot->Attribute("margin")){
        pTileSetRoot->Attribute("margin", &tileset.margin);
    } else {
        tileset.margin = 0;
    }

    
    tileset.name = pTileSetRoot->Attribute("name");
    
    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);
    
    cout << "Tileset info: " << endl;
    cout << "numColumns: " << tileset.numColumns << endl;
    
    pTilesets->push_back(tileset);
    
}

void LevelParser::parseTileLayer
(TiXmlElement *pTileElement, vector<Layer *> *pLayers,
vector<TileLayer*>* pCollisionLayers,vector<Tileset> *pTilesets){
    
    TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);
    
    //Placeholder for data
    vector<vector<int>> data;
    
    string decodedIDs;
    TiXmlElement* pDataNode= 0;
    
    bool collidable(false);
    
    //Check for layer properties
    for (TiXmlElement* e = pTileElement->FirstChildElement();
         e != NULL; e = e->NextSiblingElement()){
        cout << "Checking " << e->Value() << endl;
        if (e->Value() == string("properties")){
            for (TiXmlElement* p = e->FirstChildElement();
                 p != NULL; p = p->NextSiblingElement()){
                if (p->Value() == string("property")){
                    cout << "Now checking " << p->Value() << endl;
                    string currentProperty = p->Attribute("name");
                    
                    if (currentProperty == string("collidable")){
                        if (p->Attribute("value") == string("true")){
                            collidable = true;
                        } else {
                            collidable = false;
                        }
                        if (collidable){
                            cout << "Found collidable layer\n";
                        }
                    }
                }
            }
        }
    }
    

    //Find data node then store it
    for (TiXmlElement* e = pTileElement->FirstChildElement();
         e != NULL; e = e->NextSiblingElement()){
        if (e->Value() == string("data")){
            pDataNode = e;
        }
    }
    
    //Decode data and store
    for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling()){
        TiXmlText* text = e ->ToText();
        string t = text->Value();
        decodedIDs = base64_decode(t);
    }
    
    //Uncompress zlib compression
    uLongf numGids = m_width * m_height * sizeof(int);
    vector<unsigned> gids(numGids);
    
    uncompress
    ((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());
    
    vector<int> layerRow(m_width);

    //assign decompressed data
    for(int j = 0 ; j < m_height; j++){
        data.push_back(layerRow);
    }
    
    for (int rows = 0 ; rows <m_height; rows++){
        for (int cols = 0; cols < m_width; cols++){
            data[rows][cols] = gids[rows * m_width + cols];
        }
    }
    
    //Set Tile Layer properties
    pTileLayer->setTileIDs(data);
    pTileLayer->setNumColumns(m_width);
    pTileLayer->setNumRows(m_height);
    
    //Save new tile layer to Level
    pLayers->push_back(pTileLayer);
    
    //Add collision tiles to collision layer
    if (collidable){
        pCollisionLayers->push_back(pTileLayer);
    }
    
}

void LevelParser::parseTextures(TiXmlElement *pTextureRoot){
    cout << "Loading textures\n";
    TextureManager::Instance()->load
    (pTextureRoot->Attribute("value"),
     pTextureRoot->Attribute("name"), Game::Instance()->getRenderer());
}

void LevelParser::parseObjectLayer
(TiXmlElement *pObjectElement, vector<Layer *> *pLayers, string layerType, Level* pLevel){
    
    //Create an object layer
    ObjectLayer* pObjectLayer = new ObjectLayer();
    pObjectLayer->setType(layerType);
    cout << "Created new " << pObjectLayer->getType() << " layer\n";
    //cout << "Current Value: ";
    //cout << pObjectElement->FirstChildElement()->Value() << endl;
    
    for (TiXmlElement* e = pObjectElement->FirstChildElement();
         e != NULL; e = e->NextSiblingElement()){
        cout << "Checking " << e->Value() << endl;
        if (e->Value() == string("object")){
            int x(0), y(0), width(0), height(0), numFrames(1), callbackID(0), animSpeed(1);
            
            SDL_Color color;
            SDL_BlendMode blendMode = SDL_BLENDMODE_NONE;
            
            string textureID(""),name(""),lockTo("");
            
            //Get initial values
            e->Attribute("x", &x);
            e->Attribute("y", &y);
            //cout << "Y: " << x << "\nY: " << y << endl;
            name = e->Attribute("name");
            
            GameObject* pGameObject = GameObjectFactory::Instance()->create(e->Attribute("type"));
            
            //Get Property Values
            for (TiXmlElement* properties = e->FirstChildElement();
                 properties != NULL; properties = properties->NextSiblingElement()){
                if (properties->Value() == string("properties")){
                    
                    for (TiXmlElement* property = properties->FirstChildElement();
                         property!=NULL; property = property->NextSiblingElement()){
                        
                        if (property->Value() == string("property")){
                            
                            if (property->Attribute("name") ==
                                string("numFrames")){
                                property->Attribute("value",&numFrames);
                                
                            } else if (property->Attribute("name") == string("lockTo")){
                                lockTo = property->Attribute("value");
                                
                            } else if (property->Attribute("name") == string("textureHeight")){
                                property->Attribute("value",&height);
                                
                            } else if (property->Attribute("name") == string("textureWidth")){
                                property->Attribute("value",&width);
                                
                            } else if (property->Attribute("name") == string("animSpeed")){
                                property->Attribute("value",&animSpeed);
                                
                            } else if (property->Attribute("name") == string("callbackID")){
                                property->Attribute("value",&callbackID);
                                
                            } else if (property->Attribute("name") == string("textureID")){
                                textureID = property->Attribute("value");
                                
                            } else if (property->Attribute("name") == string("blendMode")){
                                if (property->Attribute("value") == string("add")){
                                    blendMode = SDL_BLENDMODE_ADD;
                                    //cout << "Set Blendmode!\n";
                                } else if (property->Attribute("value") == string("blend")){
                                    blendMode = SDL_BLENDMODE_BLEND;
                                } else if (property->Attribute("value") == string("mod")){
                                    blendMode = SDL_BLENDMODE_MOD;
                                }
                                
                            } else if (property->Attribute("name") == string("alpha")){
                                int temp;
                                property->Attribute("value",&temp);
                                color.a = temp;
                                //cout << "Set alpha to " << temp << endl;
                            }  else if (property->Attribute("name") == string("red")){
                                int temp;
                                property->Attribute("value",&temp);
                                color.r = temp;
                               
                            }  else if (property->Attribute("name") == string("green")){
                                int temp;
                                property->Attribute("value",&temp);
                                color.g = temp;
                               
                            }  else if (property->Attribute("name") == string("blue")){
                                int temp;
                                property->Attribute("value",&temp);
                                color.b = temp;  
                            }
                        }
                    }
                }
            }
            
            pGameObject->load
            (*new GameObjectParams
             (name, (x), (y-height),width, height, textureID,callbackID,animSpeed));
            
            //Set additional properties;
            pGameObject->GetParams().setLockTo(lockTo);
            
            //If object is player set game player pointer accordingly
            if (pObjectLayer->getType() == string("Player")){
                pLevel->setPlayer(dynamic_cast<Player*>(pGameObject));
                Game::Instance()->setPlayer(dynamic_cast<Player*>(pGameObject));
            }
            
            pObjectLayer->getGameObjects()->push_back(pGameObject);
            pGameObject->GetParams().setMaxFrames(numFrames);
            pGameObject->GetParams().setColor(color);
            pGameObject->GetParams().setBlendMode(blendMode);
            cout << "Created new " << pGameObject->GetParams().getType() << endl;
        }
    }
    pLayers->push_back(pObjectLayer);
}


































































//END