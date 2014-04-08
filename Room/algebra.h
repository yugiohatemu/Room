//
//  algebra.h
//  Room
//
//  Created by Yue Huang on 2014-04-08.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__algebra__
#define __Room__algebra__

#include <iostream>

struct Vector{
    float x, y,z;
    
    Vector();
    Vector(float x, float y,float z);
    Vector(const Vector& vec);
    float dot(Vector vec);
    Vector cross(Vector vec);
    float cross2D(Vector vec);
    
    Vector operator*(float t);
    Vector operator+(const Vector &vec);
    Vector operator=(const Vector & vec);
    bool operator==(const Vector & vec);
    bool operator!=(const Vector & vec);
    
    friend std::ostream& operator<< (std::ostream& stream, const Vector& vec);
    
    void normalize();
    float get_norm();
};

struct Point{
    float x,y,z;
	Point();
	Point(float x, float y,float z);
    Point (const Point &p);
    
    Point operator*(float s);
    Point operator/(float s);
    Point& operator= (const Point &p);
    bool operator== (const Point &p);
    bool operator!= (const Point &p);
    friend std::ostream& operator<< (std::ostream& stream, const Point& p);
};

Vector operator* (float t, const Vector & a);
Vector operator* (const Vector& a,float t);

Vector operator- (const Point &a, const Point &b);
Point operator+ (const Vector &a, const Point &b);

Point operator+ (const Point &b, const Vector &a);
#endif /* defined(__Room__algebra__) */
