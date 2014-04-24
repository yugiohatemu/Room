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
#include "ghost.h"
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

void Room::set_item_in_room(ROOM_TYPE r_type){
    room_type = r_type;
    
    if (room_type == BED_ROOM) {
        Item *bed = new Item(false);
        bed->hitbox = Rect(Point(50,50,0),150,200);
        bed->type = ITEM_BED;
        bed->turn_cost = 7;
        bed->mh_charge = 10;
        bed->ph_charge = 15;
        bed->options[0] = new Text(Point(125, 150,0),"INFO");
        bed->options[1] = new Text(Point(125, 150 + TEXT_HEIGHT,0),"USE");
        bed->info = new Text(Point(0, 400,0),"This is a comfortable bed");
        all_items.push_back(bed);
    }else if(room_type == KITCHEN){
        //
//        Item * food = new Item();
//        all_items.push_back(food);
    }else if(room_type == BOOK_ROOM){
        Item *book = new Item(false);
        book->hitbox = Rect(Point(50, 350, 0),100 ,60);
        book->type = ITEM_BOOK;
        book->turn_cost = 5;
        book->mh_charge = 5;
        book->ph_charge = -10;
        book->options[0] = new Text(Point(100, 380,0),"INFO");
        book->options[1] = new Text(Point(100, 380 + TEXT_HEIGHT,0),"USE");
        book->info = new Text(Point(0, 400,0),"There are many books in it");
        all_items.push_back(book);
    }
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
    
    //delete hidden stuff
    std::vector<Item *>::iterator it = all_items.begin();
    while (it != all_items.end()) {
        if ((*it)->hidden) {
            it = all_items.erase(it);
        }else
            it++;
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
    
    player->test_ghost->render();
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
                //Or treat it as an item first
                Instance::get().main_screen->main_room = doors[i]->next_room;
                doors[i]->next_room->player = player;
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
                    }else if(option_hit == 1){ //use or like if option_hit == USE
                        if (all_items[i]->type == ITEM_LAZY) {
                            all_items[i]->hidden = true;
                        }
                        
                        
                        player->physical_health += all_items[i]->ph_charge;
                        player->mental_health += all_items[i]->mh_charge;
                        player->turn_left -= all_items[i]->turn_cost;

                        {   //update text
                            std::stringstream ss; ss<<"PH: "<<player->physical_health;
                            Instance::get().main_screen->ph->set_text(ss.str());
                            ss.str("");
                        
                            ss<<"MH: "<<player->mental_health;
                            Instance::get().main_screen->mh->set_text(ss.str());
                            ss.str("");
                            
                            ss<<"TL: "<<player->turn_left;
                            Instance::get().main_screen->turn_left->set_text(ss.str());
                        }
                        
                        if (player->turn_left  <= 0 || all_items[i]->type == ITEM_BED) { //reset
                            Instance::get().main_screen->turn_end();
                            return ;
                        }
                        
                    }else if(false){ //option_hit == PICK UP
                        //TODO:
                    }
                    
                    dir = Vector();
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
        player->test_ghost->follow(next_pos);
        dir.normalize();
        speed = dir * speed_factor;
        
    }
    
}
