//
//  Level.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 6/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "Level.h"
#include "Layer.h"
#include "ObjectLayer.h"
#include "CollisionHandler.h"
#include "SoundManager.h"
#include "EventManager.h"
#include <vector>

using namespace std;
vector<Tileset>* Level::getTilesets(){
    return &m_tilesets;
}

vector<Layer*>* Level::getLayers(){
    return &m_layers;
}

const vector<TileLayer*>* Level::getCollidableLayers(){
    return &m_collisionLayers;
}

vector<TileLayer*>* Level::getCollisionLayers(){
    return &m_collisionLayers;
}

Level::Level(){
    //Created level
}

void Level::render(){
    for (int i = 0 ; i < m_layers.size() ; i++){
        m_layers[i]->render();
    }
}

void Level::update(){
    //Update all layers
    for (int i = 0 ; i <m_layers.size() ;i++){
        m_layers[i]->update(this);
    }
    
    checkCollisions();
}


void Level::checkCollisions(){
    //Check each layer for collision of objects
    for (int i = 0 ; i < m_layers.size() ; i++){
        for (int j = 0 ; j < m_layers.size() ; j++){
            //If layer i contains objects
            if (dynamic_cast<ObjectLayer*>(m_layers[i])){
                ObjectLayer* layer = dynamic_cast<ObjectLayer*>(m_layers[i]);
                // if layer j contains objects
                if (dynamic_cast<ObjectLayer*>(m_layers[j])){
                    ObjectLayer* layer2 = dynamic_cast<ObjectLayer*>(m_layers[j]);
                    
                    //Check objects in both layers
                    for (int x = 0 ; x < layer->getGameObjects()->size();x++){
                        for (int y = 0 ; y < layer2->getGameObjects()->size() ; y++){
                            GameObject* object1 = (*layer->getGameObjects())[x];
                            GameObject* object2 = (*layer2->getGameObjects())[y];
                            
                            //If they are not the same, check if collided
                            if (object1 != object2 &&
                                (object1->GetParams().getName() != string("Light")&&
                                 object2->GetParams().getName() != string("Light"))){
                                    if (CollisionHandler::checkCollision(object1, object2)){

                                        if (object1->GetParams().getName() == string("Player")&&
                                            object2->GetParams().getName() == string("Apple")){
                                            SoundManager::Instance()->playSound("pickup_sound");
                                            object2->GetParams().getPosition().setX(-99999);
                                            
                                            //Testing sending to event manager
                                            EventManager::Instance()->receiveEvent
                                            ("apple", "collect", 0, vector<string>());
                                        }
                                    }
                                }
                        }
                    }
                }
            }
        }
    }
}

void Level::clean(){
    while (!m_layers.empty()) {
        m_layers.back()->clean();
        m_layers.pop_back();
    }
}








































































//END