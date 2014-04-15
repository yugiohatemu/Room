//
//  door.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-15.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "door.h"
#include "instance.h"
#include "room.h"
#include <OpenGL/OpenGL.h>
#include <SDL2/SDL_opengl.h>

Door::Door(){
    
}

Door::~Door(){
    
}

void Door::render(){
    glPushMatrix();
    glColor3f(0, 0, 1);
    hitbox.render();
    glPopMatrix();
}