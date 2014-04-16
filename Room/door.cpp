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

Door::Door(Door::DOOR_DIR dir):dir(dir){
    hitbox.width = 30;
    hitbox.height = 40;
    //should based on the size of room latter.
    if (dir == NORTH) {
        hitbox.top_left = Point(SCREEN_WIDTH/2,0,0);
    }else if(dir == SOUTH){
        hitbox.top_left = Point(SCREEN_WIDTH/2,SCREEN_HEIGHT - hitbox.height - 10,0);
    }else if(dir == WEST){
        hitbox.top_left = Point(0,SCREEN_HEIGHT/2,0);
    }else if(dir == EAST){
        hitbox.top_left = Point(SCREEN_WIDTH-hitbox.width - 10, SCREEN_HEIGHT/2,0);
    }
}

Door::~Door(){
    
}

Door::DOOR_DIR Door::get_rand_dir(){
    unsigned int r = std::rand() % 4 ;
    if (r == 0) return NORTH;
    else if(r == 1) return SOUTH;
    else if(r == 2) return WEST;
    else if(r == 3) return EAST;
    return NORTH;
}

Door::DOOR_DIR Door::get_opp_dir(){
    if (dir == NORTH) return SOUTH;
    else if(dir == SOUTH) return NORTH;
    else if(dir == WEST) return EAST;
    else return WEST;
}

void Door::render(){
    glPushMatrix();
    glColor3f(0, 0, 1);
    hitbox.render();
    glPopMatrix();
}