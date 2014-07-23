//
//  ObjectLayer.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 6/24/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "ObjectLayer.h"
#include "Game.h"
#include "InputHandler.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "Vector2D.h"

void ObjectLayer::update(Level* pLevel){
    for (int i = 0 ; i < m_gameObjects.size() ; i++){
        m_gameObjects[i]->update();
    }
    

//    if (pLevel->getPlayer()){
//        CollisionManager::Instance()->
//        checkPlayerTileCollision(pLevel->getPlayer(),*pLevel->getCollidableLayers());
//    } else {
//        cout << "Could not find player\n";
//    }
    
}

void ObjectLayer::render(){
    //If dealing with a light layer, perform different render pass
    if (getType() == string("light")){
        //Create darkness texture
        SDL_Texture* darknessTexture =
        SDL_CreateTexture(Game::Instance()->getRenderer(), SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_TARGET,Game::Instance()->getGameWidth()+200,
                          Game::Instance()->getGameHeight()+200);
        
        //Store Old Color and Blendmode to restore later
        SDL_BlendMode oldBlend;
        SDL_Color oldColor;
    
        SDL_GetRenderDrawBlendMode(Game::Instance()->getRenderer(), &oldBlend);
        SDL_GetRenderDrawColor(Game::Instance()->getRenderer(),
                               &oldColor.r, &oldColor.g, &oldColor.b, &oldColor.a);
        
        
        //Set darkness layer as render surface temporarily
        SDL_SetRenderTarget(Game::Instance()->getRenderer(), darknessTexture);
    
    
        SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), currentShade.r, currentShade.g, currentShade.b, 255);
        
        //SDL_RenderClear(Game::Instance()->getRenderer());
        SDL_RenderFillRect(Game::Instance()->getRenderer(),NULL);
        
        //Render Lighting On to darkness texture
        for (int i = 0 ; i < m_gameObjects.size(); i++){
            if (m_gameObjects[i]->GetParams().getType() == string("Light")){
                
                //Make copy of current params for camera offset
                GameObjectParams cameraParams = m_gameObjects[i]->GetParams();
                
                //If light is meant to scroll, then offset it
                if (m_gameObjects[i]->GetParams().isScrolling())  {
                Vector2D pos(cameraParams.getX(),
                             cameraParams.getY());
                
                cameraParams.setX(pos.getX());
                cameraParams.setY(pos.getY());
                }
                
                
                //Flip light depending on direction
                if (m_gameObjects[i]->GetParams().getVelocity().getX() > 0){
                    TextureManager::Instance()->drawFrame
                    (&cameraParams, Game::Instance()->getRenderer(),SDL_FLIP_NONE, Game::Instance()->getZoom());
                } else {
                    TextureManager::Instance()->drawFrame
                    (&cameraParams, Game::Instance()->getRenderer(),SDL_FLIP_HORIZONTAL, Game::Instance()->getZoom());
                }
                
                //cout << "Light render\n";
                //m_gameObjects[i]->draw();
            }
        }
    
        
        //Reset Render surface
        SDL_SetRenderTarget(Game::Instance()->getRenderer(), NULL);
        SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 200, 200, 200, 255);
        SDL_SetTextureBlendMode(darknessTexture, SDL_BLENDMODE_MOD);
        SDL_SetRenderDrawBlendMode(Game::Instance()->getRenderer(), SDL_BLENDMODE_NONE);
        
        SDL_Rect src,dest;
        dest.x = dest.y = src.y = src.x = 0;
        
        dest.w = src.w = Game::Instance()->getGameWidth() + 200;
        dest.h = src.h = Game::Instance()->getGameHeight() + 200;
        
        SDL_RenderCopyEx
        (Game::Instance()->getRenderer(), darknessTexture, &src, &dest, 0, 0, SDL_FLIP_NONE);

        //Reset renderer and clear texture
        SDL_SetRenderDrawBlendMode(Game::Instance()->getRenderer(), oldBlend);
        SDL_SetRenderDrawColor(Game::Instance()->getRenderer(),
                               oldColor.r, oldColor.g, oldColor.b, oldColor.a);
        SDL_DestroyTexture(darknessTexture);
        
        //Reset render clear color
        SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0, 0, 0, 255);
        
    } else {
        //If not dealing with lights, render as normal
        for (int i = 0 ; i < m_gameObjects.size() ; i++){
        m_gameObjects[i]->draw();
        }
    }
}
