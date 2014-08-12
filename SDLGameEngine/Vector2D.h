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

template <class Type>
class Vector2D{
public:
    Vector2D();
<<<<<<< HEAD
    Vector2D(double x ,double y): m_x(x),m_y(y){};
    ~Vector2D();
    
    double getX() const { return m_x; }
    double getY() const { return m_y; }
    
    void setX(double x) { m_x = x; }
    void setY(double y) { m_y = y; }
    
    double length();
=======
    Vector2D(Type x ,Type y): m_x(x),m_y(y){};
    ~Vector2D();
    
    Type getX() const { return m_x; }
    Type getY() const { return m_y; }
    
    void setX(Type x) { m_x = x; }
    void setY(Type y) { m_y = y; }
    
    Type length();
>>>>>>> 01592973136412738e1b3cd3181cef456b96cc90
    
    void normalize();
    
    Vector2D<Type> operator+(const Vector2D<Type>& v2) const;
    friend Vector2D<Type>& operator+=(Vector2D<Type>& v1, const Vector2D<Type>& v2){
        v1.m_x += v2.m_x;
        v1.m_y += v2.m_y;
        
        return v1;
    }
    
    Vector2D<Type> operator-(const Vector2D<Type>& v2) const;
    friend Vector2D<Type>& operator-=(Vector2D<Type>& v1, const Vector2D<Type>& v2){
        v1.m_x -= v2.m_x;
        v1.m_y -= v2.m_y;
        
        return v1;
    }
    
<<<<<<< HEAD
    Vector2D operator*(double scalar);
    Vector2D& operator*=(double scalar);
    
    Vector2D operator/(double scalar);
    Vector2D& operator/=(double scalar);
    
private:
    double m_x;
    double m_y;
=======
    Vector2D<Type> operator*(Type scalar);
    Vector2D<Type>& operator*=(Type scalar);
    
    Vector2D<Type> operator/(Type scalar);
    Vector2D<Type>& operator/=(Type scalar);
    
private:
    Type m_x;
    Type m_y;
};



template <class Type> Vector2D<Type>::Vector2D(): Vector2D<Type>(0,0){
}

template <class Type> Vector2D<Type>::~Vector2D(){
>>>>>>> 01592973136412738e1b3cd3181cef456b96cc90
    
    //cout << "Deleted vector2d\n";
}

template <class Type> Type Vector2D<Type>::length(){
    return sqrt(m_x * m_x + m_y + m_y);
}

template <class Type> Vector2D<Type> Vector2D<Type>::operator+(const Vector2D& v2) const {
    return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
}

template <class Type> Vector2D<Type> Vector2D<Type>::operator-(const Vector2D& v2) const{
    return Vector2D(m_x - v2.m_x , m_y - v2.m_y);
}

template <class Type> Vector2D<Type> Vector2D<Type>::operator*(Type scalar){
    return Vector2D(m_x * scalar , m_y * scalar);
}

template <class Type> Vector2D<Type>& Vector2D<Type>::operator*=(Type scalar){
    m_x *= scalar;
    m_y *= scalar;
    
    return *this;
}

template <class Type> Vector2D<Type> Vector2D<Type>::operator/(Type scalar){
    return Vector2D(m_x/scalar , m_y/scalar);
}

template <class Type> Vector2D<Type>& Vector2D<Type>::operator/=(Type scalar){
    m_x/=scalar;
    m_y/=scalar;
    
    return *this;
}

template <class Type> void Vector2D<Type>::normalize(){
    Type len = length();
    
    if (len > 0){
        (*this) *= 1 / len ;
    }
}




#endif /* defined(__LudumDare29__Vector2D__) */







































































//END