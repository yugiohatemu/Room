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
#include "text.h"
#include <GLUT/GLUT.h>

Item::Item(bool lazy):lazy(lazy){
    option_hidden = true;
    info_hidden = true;
    options[0] = NULL;
    options[1] = NULL;
    info = NULL;
    //or we should show info directly on clicked based
    ph_charge = 0;
    mh_charge = 0;
    turn_cost = 0;
}

Item::~Item(){
    if(options[0]) delete options[0];
    if(options[1]) delete options[1];
    if (info) delete info;
}

void Item::render(){
    
    if (lazy) {
        glPushMatrix();
        glColor4f(1, 1, 0, 0.5);
        hitbox.render();
        glColor3f(0, 0, 0);
        
        glRasterPos2f(hitbox.top_left.x, hitbox.top_left.y + 24);
        for (unsigned int i = 0; i < item_name.length() ; i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, item_name[i]);
        }
        
        glPopMatrix();
    }else{
        glPushMatrix();
        GLuint texture_ID = Instance::get().texture().get_texture(Texture::ITEM);
        
        glBindTexture(GL_TEXTURE_2D, texture_ID);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        //0,1,2,3
        //x,y,w,h
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
    }
    
    
    
    if (!option_hidden) {
        for (unsigned int i = 0; i < 2; i++) {
            if(options[i])options[i]->render();
        }
    }
    if (!info_hidden) {
        if(info) info->render();
    }
    
    
    glPopMatrix();
}

bool Item::is_item_being_hit(Point pos){
    for (unsigned int i = 0; i < 2; i++) {
        if ( options[i]&&options[i]->hitbox.is_pos_in_rec(pos)) return true;
    }
    return hitbox.is_pos_in_rec(pos);
}

//-1 is hiting on the original
int Item::get_option_being_hit(Point pos){
    for (unsigned int i = 0; i < 2; i++) {
        if (options[i]&&options[i]->hitbox.is_pos_in_rec(pos)) return i;
    }
    return -1;
}

