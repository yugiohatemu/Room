//
//  algebra.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-08.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "algebra.h"
#include <math.h>
#include <sstream>

#define PI 3.1415926

Vector::Vector(){
    x = y = z = 0.f;
}

Vector::Vector(float x, float y, float z):x(x), y(y), z(z){
    
}

Vector::Vector(const Vector &vec){
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

Vector Vector::operator*(float t){
    return Vector(t*x,t*y,t*z);
}

Vector Vector::operator+(const Vector &vec){
    return Vector(x + vec.x, y + vec.y, z + vec.z);
}

Vector Vector::operator=(const Vector & vec){
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
}

bool Vector::operator==(const Vector & vec){
    return x == vec.x && y == vec.y && z == vec.z;
}

bool Vector::operator!=(const Vector & vec){
    return x != vec.x || y != vec.y || z != vec.z;
}

std::ostream& operator<< (std::ostream& stream, const Vector& vec){
    stream<<"[VEC] ["<<vec.x<<","<<vec.y<<","<<vec.z<<"]";
    return stream;
}

void Vector::normalize(){
    float n = get_norm();
    if (n != 0) {
        x = x/n;
        y = y/n;
        z = z/n;
    }
}

float Vector::get_norm(){
    return sqrtf(x*x + y*y+ z*z);
}

float Vector::dot(Vector vec){
    return x * vec.x + y * vec.y + z * vec.z;
}

Vector Vector::cross(Vector vec){
    return Vector(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}


/////////////////////////////////////////////
Point::Point() {
    x = y = z = 0.f;
}

Point::Point(float x, float y,float z):x(x),y(y),z(z){
    
}

Point::Point (const Point &p){
    x = p.x;
    y = p.y;
    z = p.z;
}

Point Point::operator*(float s){
    return Point(x*s,y*s,z*s);
}

Point Point::operator/(float s){
    if ( s == 0) return *this;
    else return Point(x/s,y/s,z/s);
}

Point& Point::operator= (const Point &p){
    if (this == &p) {
        return *this;
    }
    x = p.x;
    y = p.y;
    z = p.z;
    return *this;
}

bool Point::operator== (const Point &p){
    return x == p.x && y == p.y && z == p.z;
}

bool Point::operator!= (const Point &p){
    return x != p.x || y != p.y || z !=p.z;
}

std::ostream& operator<< (std::ostream& stream, const Point& p){
    stream<<"[POT] ("<<p.x<<","<<p.y<<","<<p.z<<")";
    return stream;
}

////////////////////////////////////////////////////////////
Vector operator* (float t, const Vector & a){
    return Vector(t * a.x, t * a.y, t * a.z);
}

Vector operator* (const Vector& a,float t){
    return Vector(t * a.x, t * a.y, t * a.z);
}

Vector operator- (const Point &a, const Point &b){
    return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

Point operator+ (const Vector &a, const Point &b){
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point operator+ (const Point &b, const Vector &a){
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}
