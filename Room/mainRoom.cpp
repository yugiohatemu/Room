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
    pos.z = 0;
    next_pos = pos;
    speed_factor = 5;
    obstacle = new Item();
}

MainRoom::~MainRoom(){
    delete obstacle;
}

void MainRoom::render(){
    //Event unrelated update
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
    
    obstacle->render();
    
    glPushMatrix();
    
    glColor3f(1, 0, 0);
    glTranslatef(pos.x, pos.y, 0);
    
    glBegin( GL_QUADS );
    glVertex2f( 0 , 0  ); glVertex2f( 0 , 50 );
    glVertex2f( 50, 50 ); glVertex2f( 50, 0  );
    glEnd();
    
    glPopMatrix();
}

void MainRoom::update(SDL_Event event){
  
    if( event.type == SDL_MOUSEBUTTONDOWN ){
        
        int x, y; SDL_GetMouseState( &x, &y );
        Point new_pos(x,y,0);
        if (next_pos == new_pos) return;

        Vector dir = new_pos - pos;
        float dis = dir.get_norm();
        
        //Get the closeset one as the real next_pos;
        for (unsigned int i = 0; i < 1; i++) {
            Vector next_dir = obstacle->get_closest_dir(pos, dir);
            float next_dis = next_dir.get_norm();
                    
            if (next_dis < dis) {
                dis = next_dis;
                dir = next_dir;
            }
        
        }
        
        for (unsigned int i = 0; i < 1; i++) {
            if (obstacle->is_item_being_hit(new_pos)) {
                
                if (obstacle->is_option_visible) {
                    
                    int option_hit = obstacle->get_option_being_hit(new_pos);
                    if (option_hit != -1) { //hit actually happens on option
                        std::cout<<"Hit option "<<option_hit<<std::endl;
                    }
                    break;
                }else { //close enough
                    obstacle->is_option_visible = true;
                    break;
                    
                }
            }else{
                obstacle->is_option_visible = false;
            }

        }
        
        next_pos = pos + dir;
        dir.normalize();
        speed = dir * speed_factor;
        
    }
    
}
