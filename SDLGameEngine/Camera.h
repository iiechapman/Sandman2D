//
//  Camera.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 7/11/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__Camera__
#define __SDLGameDevelopmentChapter1__Camera__

#include <iostream>
#include "Vector2D.h"

using namespace std;

class Camera{
public:
    static Camera* Instance(){
        if (s_pCamera == 0){
            s_pCamera = new Camera();
        }
        return s_pCamera;
    }
    
    void reset();
    void update();
    void setTarget(Vector2D* target){
        m_pTarget = target;
    }
    void setPosition(Vector2D& position){
        m_position = position;
    }
    
    const Vector2D getPosition();
    
    
private:
    Camera();
    ~Camera();
    
    //Cameras target to follow
    Vector2D* m_pTarget;
    
    //Cameras position
    Vector2D m_position;
    
    //Singleton
    static Camera* s_pCamera;
    
    bool m_bSmoothScroll = false;
    
};


#endif /* defined(__SDLGameDevelopmentChapter1__Camera__) */
