//
//  Item.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "Item.h"
#include "InputHandler.h"

Item::Item(){
    //cout << "Created new Item\n";
    //m_params = new GameObjectParams();
    m_params.setType("Item");
}

Item::Item(GameObjectParams params , int numberFrames)
:SDLGameObject(params){
    GetParams().setVelocity({0,0});
    GetParams().setMaxFrames(numberFrames);
}

void Item::load(GameObjectParams params){
    SDLGameObject::load(params);
}

void Item::collision(){
    
}

void Item::draw(){
    SDLGameObject::draw();
}

void Item::update(){
    //cout << "Total Frames: " << GetParams().getTotalFrames() << " Speed: " << GetParams().getAnimSpeed() << endl;
    
    //Check events
    while (GetParams().getEvents()->getSize() > 0) {
        Event* event = GetParams().getEvents()->getTopEvent();
        cout << "Checking event " << event->getEventName() << endl;
        //Collect event moves object away
        if (event->getEventName() == string("collect")){
            GetParams().getPosition().setX(-99999);
        }
        
    }
    
    if (GetParams().aiEnabled()){
        
        int switchState = rand() % 100;
        
        switch (switchState) {
            case 0:
                GetParams().setAIState(MOVE_NONE);
                break;
                
            case 1:
                GetParams().setAIState(MOVE_RIGHT);
                break;
                
            case 2:
                GetParams().setAIState(MOVE_LEFT);
                break;
                
            default:
                break;
        }
        
        switch (GetParams().getAIState()) {
            case MOVE_RIGHT:
                GetParams().getPosition().setX(GetParams().getPosition().getX()+1);
                break;
                
            case MOVE_LEFT:
                GetParams().getPosition().setX(GetParams().getPosition().getX()-1);
                break;
                
                
            default:
                break;
        }
    }
    
    if (GetParams().getTotalFrames()>0 && GetParams().getAnimSpeed()>0){
        GetParams().setFrame
        (GetParams().getStartFrame() +(int((SDL_GetTicks()/ ((1000 / GetParams().getAnimSpeed())) % GetParams().getTotalFrames()))));
    } else {
        GetParams().setFrame(0);
    }
    
    SDLGameObject::update();
}

void Item::clean(){
    SDLGameObject::clean();
    cout << "Cleaning Item\n";
}






















































//END