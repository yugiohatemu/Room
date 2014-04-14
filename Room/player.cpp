//
//  player.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-14.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "player.h"
#include <OpenGL/OpenGL.h>
#include <SDL2/SDL_opengl.h>
#include "instance.h"

Player::Player(){
    type = ITEM_PLAYER;
    //Player is going to have their seperate enum later ...
    physical_health = 100;
    mental_health = 100;
    progress_of_x = 0;
}

Player::~Player(){
    
}

void Player::render(){
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
    glTexCoord2f(ITEM_CLIP[4 * type], ITEM_CLIP[4 * type + 1]+ ITEM_CLIP[4 * type + 3]);
    glVertex2f(hitbox.points[3].x, hitbox.points[3].y);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

}