//
//  Room.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-08.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "room.h"
#include <OpenGL/OpenGL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <sstream>
#include "instance.h"
#include "item.h"
#include "player.h"
#include "text.h"
#include "interScreen.h"
#include "mainScreen.h"
#include "door.h"

unsigned int tag_conunter = 0;

Room::Room(){
    pos = Point(240, 320,0);
    next_pos = pos;
    speed_factor = 5;

    hitbox = Rect(Point(), SCREEN_WIDTH, SCREEN_HEIGHT);
    
    tag = tag_conunter;
    tag_conunter++;
    std::cout<<"Create Room "<<tag<<std::endl;
    
    player = NULL;
}

Room::~Room(){
    std::cout<<"Delete Room "<<tag<<std::endl;
    for (unsigned int i = 0; i < all_items.size(); i++) {
        delete all_items[i];
    }
    for(unsigned int i = 0; i < doors.size();i++){
        delete doors[i];
    }
}

void Room::reset(){
    pos.x = 240; pos.y = 320;

    next_pos = pos;
    
    for(unsigned int i =0;i < all_items.size();i++){
        all_items[i]->option_hidden = true;
        all_items[i]->info_hidden = true;
    }
    player = NULL;
}

void Room::render(){
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
    for(unsigned int i = 0; i < doors.size();i++){
        doors[i]->render();
    }
    for (unsigned int i = 0; i < all_items.size(); i++) {
        all_items[i]->render();
    }
        
    glPushMatrix();
    glTranslatef(pos.x, pos.y, 0);
    if(player) player->render();
    glPopMatrix();
    
}

void Room::update(SDL_Event event){
  
    if( event.type == SDL_MOUSEBUTTONDOWN ){
        
        int x, y; SDL_GetMouseState( &x, &y );
        Point new_pos(x,y,0);
        //If same or outside the room range, do nothing...
        if (next_pos == new_pos || !hitbox.is_pos_in_rec(new_pos)) return;
        
        Vector dir = new_pos - pos;
        float dis = dir.get_norm();
        
        for (unsigned int i = 0; i < doors.size(); i++) {
            if (doors[i]->hitbox.is_pos_in_rec(new_pos)) {
                //TODO: perform animation to walk to the door
                Instance::get().main_screen->set_main_room(doors[i]->next_room);
                return ;
            }
        }
        //Get the closeset one as the real next_pos;
        for (unsigned int i = 0; i < all_items.size(); i++) {
            Vector next_dir = all_items[i]->hitbox.get_closest_dir(pos, dir);
            float next_dis = next_dir.get_norm();
                    
            if (next_dis < dis) {
                dis = next_dis;
                dir = next_dir;
            }
        
        }
        //we can get a vector here, just to make things easy?
        for (unsigned int i = 0; i < all_items.size(); i++) {
            if (all_items[i]->is_item_being_hit(new_pos)) {
                
                if (!all_items[i]->option_hidden) { //note, here should be option->hidden
                    
                    int option_hit = all_items[i]->get_option_being_hit(new_pos);
                    if (option_hit != -1) { //hit actually happens on option
//                        std::cout<<"Hit option "<<option_hit<<std::endl;
                    }
                    
                    if (option_hit == 0) { //0
                        all_items[i]->info_hidden = false;
                    }else if(option_hit == 1){ //use
                        player->physical_health += all_items[i]->ph_charge;
                        player->mental_health += all_items[i]->mh_charge;
                        player->turn_left -= all_items[i]->turn_cost;
                        std::cout<<"Ph -  "<<player->physical_health<<" mh - "<<player->mental_health<<" turn left "<< player->turn_left<<std::endl;
                        if (player->turn_left  <= 0) { //reset
                            
                            Instance::get().screen_shown = Instance::INTER_SCREEN;
                            Instance::get().inter_screen->text->set_text("Next Day");
                            Instance::get().main_screen->turn_end();
                            return ;

                        }
                        
                    }
                    break;
                }else { //close enough
                    all_items[i]->option_hidden = false;
                }
            }else{
                all_items[i]->option_hidden = true;
                all_items[i]->info_hidden = true;
            }

        }
        
        next_pos = pos + dir;
        dir.normalize();
        speed = dir * speed_factor;
        
    }
    
}
