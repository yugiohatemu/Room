//
//  rect.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-08.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "rect.h"
#include <OpenGL/OpenGL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
Rect::Rect(){
    
}

Rect::Rect(Point top_left, int width, int height):top_left(top_left), width(width),height(height){
}

void Rect::render(){
    //0 1
    //3 2
    glBegin(GL_QUADS);
    glVertex2f(top_left.x, top_left.y);
    glVertex2f(top_left.x + width, top_left.y);
    glVertex2f(top_left.x + width, top_left.y + height);
    glVertex2f(top_left.x, top_left.y + height);
    glEnd();
}

bool Rect::is_pos_in_rec(Point pos){
    return (pos.x >= top_left.x && pos.x <= top_left.x + width && pos.y >= top_left.y && pos.y <= top_left.y + height);
}

Vector Rect::get_closest_dir(Point pos, Vector dir){
    //lazy cheat to create cycle
    float t = 1.0f;
    Point points[5];
    points[0] = top_left;
    points[1] = points[0]; points[1].x += width;
    points[2] = points[1]; points[2].y += height;
    points[3] = points[0]; points[3].y += height;
    points[4] = points[0];
    
    for (unsigned int i = 0; i < 4; i++) { //x * vec.y - y * vec.x
        Vector edge_vec = points[i+1]- points[i];
        float div_down = dir.x * edge_vec.y - dir.y * edge_vec.x;
        
        if (div_down != 0) {
            Vector ray = points[i]- pos;
            float next_t = (ray.x * edge_vec.y - ray.y * edge_vec.x) /div_down;
            float next_u = (ray.x * dir.y - ray.y * dir.x) / div_down;
            
            //within line segment, and less than the previous one, replace it
            if (next_t > 0 &&  next_t < t && next_u >= 0 && next_u <= 1) t = next_t;
        }
    }
    
    return dir * t;
}
