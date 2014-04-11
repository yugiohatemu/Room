//
//  item.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-09.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "item.h"
#include <OpenGL/OpenGL.h>
#include <SDL2/SDL_opengl.h>
#include "instance.h"
Item::Item(){
    hidden = true;

    options[0] = Rect(Point(100,50,0), 70, 50); //should be text
    options[1] = Rect(Point(100,110,0), 70, 50);
}

Item::~Item(){
}

void Item::render(){
    glPushMatrix();
    GLuint texture_ID = Instance::get().texture().get_texture(Texture::ITEM);
    
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBegin(GL_QUADS);
    glTexCoord2f(ITEM_CLIP[4 * type], ITEM_CLIP[4 * type + 1]);
    glVertex2f(hitbox.points[0].x, hitbox.points[0].y);
    glTexCoord2f(ITEM_CLIP[4 * type] + ITEM_CLIP[4 * type + 2], ITEM_CLIP[4 * type + 1]);
    glVertex2f(hitbox.points[1].x, hitbox.points[1].y);
    glTexCoord2f(ITEM_CLIP[4 * type] + ITEM_CLIP[4 * type + 2], ITEM_CLIP[4 * type + 1] + ITEM_CLIP[4 * type + 3]);
    glVertex2f(hitbox.points[2].x, hitbox.points[2].y);
    glTexCoord2f(ITEM_CLIP[4 * type], ITEM_CLIP[4 * type + 1]+ ITEM_CLIP[4 * type + 2]);
    glVertex2f(hitbox.points[3].x, hitbox.points[3].y);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glColor3f(0, 1, 1);
    if (!hidden) {
        glColor3f(1, 1, 0);
        for (unsigned int i = 0; i < 2; i++) options[i].render();
    }
    glPopMatrix();
}

Vector Item::get_closest_dir(Point pos, Vector dir){
    //check against each interscetion
    int order[] = {0,1,2,3,0}; //lazy cheat for cycle
    float t = 1.0f;
    for (unsigned int i = 0; i < 4; i++) { //x * vec.y - y * vec.x
        Vector edge_vec = hitbox.points[order[i+1]]- hitbox.points[order[i]];
        float div_down = dir.x * edge_vec.y - dir.y * edge_vec.x;
        
        if (div_down != 0) {
            Vector ray = hitbox.points[order[i]]- pos;
            float next_t = (ray.x * edge_vec.y - ray.y * edge_vec.x) /div_down;
            float next_u = (ray.x * dir.y - ray.y * dir.x) / div_down;
            
            //within line segment, and less than the previous one, replace it
            if (next_t > 0 &&  next_t < t && next_u >= 0 && next_u <= 1) t = next_t;
        }
    }
    
    return dir * t;
}

bool Item::is_item_being_hit(Point pos){
    for (unsigned int i = 0; i < 2; i++) {
        if (options[i].is_pos_in_rec(pos)) return true;
    }
    return hitbox.is_pos_in_rec(pos);
}

//-1 is hiting on the original
int Item::get_option_being_hit(Point pos){
    for (unsigned int i = 0; i < 2; i++) {
        if (options[i].is_pos_in_rec(pos)) return i;
    }
    return -1;
}

