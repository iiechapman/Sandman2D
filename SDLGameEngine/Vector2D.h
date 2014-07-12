//
//  Vector2D.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/30/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __LudumDare29__Vector2D__
#define __LudumDare29__Vector2D__

#include <iostream>
#include <cmath>
using namespace std;

class Vector2D{
public:
    Vector2D();
    Vector2D(float x ,float y): m_x(x),m_y(y){};
    ~Vector2D();
    
    float getX() const { return m_x; }
    float getY() const { return m_y; }
    
    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }
    
    float length();
    
    void normalize();
    
    Vector2D operator+(const Vector2D& v2) const;
    friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2){
        v1.m_x += v2.m_x;
        v1.m_y += v2.m_y;
        
        return v1;
    }
    
    Vector2D operator-(const Vector2D& v2) const;
    friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2){
        v1.m_x -= v2.m_x;
        v1.m_y -= v2.m_y;
        
        return v1;
    }
    
    Vector2D operator*(float scalar);
    Vector2D& operator*=(float scalar);
    
    Vector2D operator/(float scalar);
    Vector2D& operator/=(float scalar);
    
private:
    float m_x;
    float m_y;
    
    
    
};


#endif /* defined(__LudumDare29__Vector2D__) */







































































//END