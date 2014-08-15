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

                                            //Create two events
                                            vector<Event*> events;
                                            vector<string> arguments;
                                            string argument = "";
                                            
                                            //Collect event
                                            Event* event = new Event
                                            ("apple", object2->GetParams().getEvents(),
                                             "collect", 0, arguments);
                                    
                                            events.push_back(event);
                                            event = 0;
                                            arguments.clear();
                                            
                                            //Sound effect event
                                            argument = "pickup_sound";
                                            arguments.push_back(argument);
                                            event = new Event
                                            ("apple", 0,"play_sound", 1, arguments);
                                            
                                            cout << "Sent Event!\n";
                                            events.push_back(event);
                                            
                                            //Testing sending to event manager
                                            EventManager::Instance()->receiveEvent(&events);
                                        }
                                        
                                        if (object1->GetParams().getName() == string("Player")&&
                                           object2->GetParams().getName() == string("Crystal")){
                                            
                                            //Create two events
                                            vector<Event*> events;
                                            vector<string> arguments;
                                            string argument1 = "800";
                                            string argument2 = "440";
                                            arguments.push_back(argument1);
                                            arguments.push_back(argument2);
                                            
                                            //Teleport event
                                            Event* event = new Event
                                            ("crystal", object1->GetParams().getEvents(),
                                             "set_position", 2, arguments);
                                            
                                            arguments.clear();
                                            
                                            //Sound effect event
                                            argument1 = "teleport_sound";
                                            arguments.push_back(argument1);
                                            
                                            event = new Event
                                            ("crystal", 0,"play_sound", 1, arguments);
                                            
                                            cout << "Sent Event!\n";
                                            events.push_back(event);
                                            
                                            //Testing sending to event manager
                                            EventManager::Instance()->receiveEvent(&events);
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