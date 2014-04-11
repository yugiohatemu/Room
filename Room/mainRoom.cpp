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
#include "instance.h"

MainRoom::MainRoom(){
    pos.x = 240;
    pos.y = 320;
    pos.z = 0;
    next_pos = pos;
    speed_factor = 5;
    //TODO: set options to be text
    bed = new Item();
    bed->hitbox = Rect(Point(50,50,0),150,200);
    bed->type = ITEM_BED;
    
    //yap...
    X = new Item();
    X->hitbox = Rect(Point(500, 50, 0),80 ,80);
    X->type = ITEM_X;
    //
    book = new Item();
    book->hitbox = Rect(Point(50, 350, 0),100 ,60);
    book->type = ITEM_BOOK;
    
    //push everything into a vector...yap
}

MainRoom::~MainRoom(){
    delete bed;
    delete X;
    delete book;
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
    
    bed->render();
    X->render();
    book->render();
    
    Instance::get().bottomInfo().render();

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
            Vector next_dir = bed->get_closest_dir(pos, dir);
            float next_dis = next_dir.get_norm();
                    
            if (next_dis < dis) {
                dis = next_dis;
                dir = next_dir;
            }
        
        }
        //we can get a vector here, just to make things easy?
        for (unsigned int i = 0; i < 1; i++) {
            if (bed->is_item_being_hit(new_pos)) {
                
                if (!bed->hidden) { //note, heere should be option->hidden
                    
                    int option_hit = bed->get_option_being_hit(new_pos);
                    if (option_hit != -1) { //hit actually happens on option
                        std::cout<<"Hit option "<<option_hit<<std::endl;
                    }
                    if (option_hit == 0) { //0
                        //set the info on bottom pop up
                        Instance::get().bottomInfo().set_info("Hi\n"); //get info from the option in futrue
                        Instance::get().bottomInfo().hidden = false;
                    }
                    break;
                }else { //close enough
                    bed->hidden = false;
//                    Instance::get().bottomInfo().hidden = false;
                    break;
                    
                }
            }else{
                bed->hidden = true;
                Instance::get().bottomInfo().hidden = true;
            }

        }
        
        next_pos = pos + dir;
        dir.normalize();
        speed = dir * speed_factor;
        
    }
    
}
