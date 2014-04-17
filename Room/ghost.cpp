//
//  ghost.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-17.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "ghost.h"
#include <OpenGL/OpenGL.h>
#include <SDL2/SDL_opengl.h>
#include "instance.h"

Ghost::Ghost(){
    type = ITEM_GHOST;
    hitbox = Rect(Point(),40,120);
    pos = Point(240, 320,0);
    next_pos = pos;
    speed_factor = 4;
}

Ghost::~Ghost(){
    
}

void Ghost::follow(Point new_pos){
    //whithin maybe 40 pixel
    Vector new_dir = new_pos - pos;
    float dis = new_dir.get_norm();

    if (dis > 40) {
        next_pos = pos + new_dir * (1 - 40 / dis);
    }else{
        next_pos = new_pos;
    }
    dir = next_pos - pos;
    dir.normalize();
    dir = dir * speed_factor;

}

void Ghost::render(){
    if (next_pos != pos) {
        float dis =  (next_pos - pos).get_norm();
        if (dis > dir.get_norm()) {
            pos = pos + dir;
        }else{ //if we are close enough
            pos = next_pos;
            dir.x = 0;
            dir.y = 0;
        }
    }
    
    glPushMatrix();
    GLuint texture_ID = Instance::get().texture().get_texture(Texture::ITEM);
    
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  
    glTranslatef(pos.x, pos.y, 0);
    Point top_left = hitbox.top_left;
    glBegin(GL_QUADS);
    glTexCoord2f(ITEM_CLIP[4 * type], ITEM_CLIP[4 * type + 1]);
    glVertex2f(top_left.x, top_left.y);
    glTexCoord2f(ITEM_CLIP[4 * type] + ITEM_CLIP[4 * type + 2], ITEM_CLIP[4 * type + 1]);
    glVertex2f(top_left.x + hitbox.width, top_left.y);
    glTexCoord2f(ITEM_CLIP[4 * type] + ITEM_CLIP[4 * type + 2], ITEM_CLIP[4 * type + 1] + ITEM_CLIP[4 * type + 3]);
    glVertex2f(top_left.x + hitbox.width, top_left.y + hitbox.height);
    glTexCoord2f(ITEM_CLIP[4 * type], ITEM_CLIP[4 * type + 1]+ ITEM_CLIP[4 * type + 3]);
    glVertex2f(top_left.x, top_left.y + hitbox.height);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}