//
//  Vector2D.cpp
//  LudumDare29
//
//  Created by Evan Chapman on 4/30/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "Vector2D.h"

Vector2D::Vector2D(): Vector2D(0,0){
}

Vector2D::~Vector2D(){
    //cout << "Deleted vector2d\n";
}

float Vector2D::length(){
    return sqrt(m_x * m_x + m_y + m_y);
}

Vector2D Vector2D::operator+(const Vector2D& v2) const {
    return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
}

Vector2D Vector2D::operator-(const Vector2D& v2) const{
    return Vector2D(m_x - v2.m_x , m_y - v2.m_y);
}

Vector2D Vector2D::operator*(float scalar){
    return Vector2D(m_x * scalar , m_y * scalar);
}

Vector2D& Vector2D::operator*=(float scalar){
    m_x *= scalar;
    m_y *= scalar;
    
    return *this;
}

Vector2D Vector2D::operator/(float scalar){
    return Vector2D(m_x/scalar , m_y/scalar);
}

Vector2D& Vector2D::operator/=(float scalar){
    m_x/=scalar;
    m_y/=scalar;
    
    return *this;
}

void Vector2D::normalize(){
    float len = length();
    
    if (len > 0){
        (*this) *= 1 / len ;
    }
}