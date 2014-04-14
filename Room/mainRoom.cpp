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
#include "item.h"
#include "player.h"

MainRoom::MainRoom(){
    pos = Point(240, 320,0);
    next_pos = pos;
    speed_factor = 5;
    one_turn = ONE_TURN_COST;
    
    
    //TODO: set options to be text
    Item *bed = new Item();
    bed->hitbox = Rect(Point(50,50,0),150,200);
    bed->type = ITEM_BED;
    bed->turn_cost = 0;
    //yap...
    Item *X = new Item();
    X->hitbox = Rect(Point(500, 50, 0),80 ,80);
    X->type = ITEM_X;
    X->turn_cost = 0;
    //
    Item *book = new Item();
    book->hitbox = Rect(Point(50, 350, 0),100 ,60);
    book->type = ITEM_BOOK;
    book->turn_cost = 0;
    
    //push everything into a vector...yap
    all_items.push_back(bed);
    all_items.push_back(X);
    all_items.push_back(book);
    
    player = new Player();
    player->hitbox = Rect(Point(),40,120);
}

MainRoom::~MainRoom(){
    for (unsigned int i = 0; i < all_items.size(); i++) {
        delete all_items[i];
    }
    delete player;
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
    
    for (unsigned int i = 0; i < all_items.size(); i++) {
        all_items[i]->render();
    }
    
    Instance::get().bottomInfo().render();

    glPushMatrix();
    glTranslatef(pos.x, pos.y, 0);
    player->render();
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
        for (unsigned int i = 0; i < all_items.size(); i++) {
            Vector next_dir = all_items[i]->get_closest_dir(pos, dir);
            float next_dis = next_dir.get_norm();
                    
            if (next_dis < dis) {
                dis = next_dis;
                dir = next_dir;
            }
        
        }
        //we can get a vector here, just to make things easy?
        for (unsigned int i = 0; i < all_items.size(); i++) {
            if (all_items[i]->is_item_being_hit(new_pos)) {
                
                if (!all_items[i]->hidden) { //note, here should be option->hidden
                    
                    int option_hit = all_items[i]->get_option_being_hit(new_pos);
                    if (option_hit != -1) { //hit actually happens on option
                        std::cout<<"Hit option "<<option_hit<<std::endl;
                    }
                    
                    if (option_hit == 0) { //0
                        //get info from the option in futrue
                        Instance::get().bottomInfo().set_info("Hi\n");
                        Instance::get().bottomInfo().hidden = false;
                    }else if(option_hit == 1){ //use
                        //TODO:
                        player->physical_health += all_items[i]->ph_charge;
                        player->mental_health += all_items[i]->mh_charge;
                        one_turn -= all_items[i]->turn_cost;
                        if (one_turn <= 0) { //reset
                            one_turn = ONE_TURN_COST;
                            //reset
                        }
                        
                    }
                    break;
                }else { //close enough
                    all_items[i]->hidden = false;
                }
            }else{
                all_items[i]->hidden = true;
                Instance::get().bottomInfo().hidden = true;
            }

        }
        
        next_pos = pos + dir;
        dir.normalize();
        speed = dir * speed_factor;
        
    }
    
}
