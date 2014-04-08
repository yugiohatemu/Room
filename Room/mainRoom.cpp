//
//  mainRoom.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-08.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "mainRoom.h"
#include <OpenGL/OpenGL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>

MainRoom::MainRoom(){
    pos.x = 240;
    pos.y = 320;
    next_pos = pos;
    speed_factor = 5;
}

MainRoom::~MainRoom(){
    
}

void MainRoom::render(){
    if (next_pos != pos) {
        float dis =  (next_pos - pos).get_norm();
        if (dis > speed.get_norm()) {
            pos = pos + speed;
        }else{ //if we are close enough
            pos = next_pos;
            speed.x = 0;
            speed.y = 0;
        }
    }
    
    glPushMatrix();
    
    glColor3f(1, 0, 0);
    glTranslatef(pos.x, pos.y, pos.z);
    
    glBegin( GL_QUADS );
    glVertex2f( 0 , 0  ); glVertex2f( 0 , 50 );
    glVertex2f( 50, 50 ); glVertex2f( 50, 0  );
    glEnd();
    
    glPopMatrix();
}

void MainRoom::update(SDL_Event event){
  
    if( event.type == SDL_MOUSEBUTTONDOWN ){

        int x, y;
        SDL_GetMouseState( &x, &y );
        
        Point new_pos(x,y,0);
        
        if (new_pos != next_pos) {
            //recalculate the vector
            next_pos = new_pos;
            speed = next_pos - pos;
            speed.normalize();
            speed = speed * speed_factor;
        }
    }

    
}
