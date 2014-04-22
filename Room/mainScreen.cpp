//
//  mainScreen.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-14.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "mainScreen.h"
#include "room.h"
#include "player.h"
#include "door.h"
#include "item.h"
#include "instance.h"
#include "text.h"
#include "interScreen.h"
#include <sstream>

MainScreen::MainScreen(){
    player = new Player();
    player->hitbox = Rect(Point(),40,120);
    
    ph = new Text(Point(), "PH: 100");
    mh = new Text(Point(300,0,0), "MH: 100");
    turn_left = new Text(Point(500,0,0), "TL: 24");
    srand(time(NULL));
    unsigned int start_room_size = 5;
    for (unsigned int i = 0; i < start_room_size; i++) make_room();
    
    //the 1st and last is always fixed here
    rooms.front()->set_item_in_room(Room::BED_ROOM);
    rooms.back()->set_item_in_room(Room::BOOK_ROOM);
    
    //set it
    main_room = rooms.front();
    main_room->player = player;
}

MainScreen::~MainScreen(){
    for (unsigned int i = 0; i < rooms.size(); i++) {
        if (rooms[i]) delete rooms[i];
    }
    delete player;
    delete ph;
    delete mh;
    delete turn_left;
}

void MainScreen::render(){
    main_room->render();
    ph->render();
    mh->render();
    turn_left->render();
    //render health
}

void MainScreen::update(SDL_Event event){
    main_room->update(event);
}

void MainScreen::make_room(){
    //If starting with nothing
    if (rooms.empty()) {
        rooms.push_back(new Room());
        return ;
    }
    
    //eLse
    //select a random room
    Room * selected_room = rooms[rand() % rooms.size()];
    //pick a direction, and find the matching direction with it
    Door * d1 = new Door(Door::get_rand_dir());
    //get position on the part and check against other door (if we have that might intersect it)
    //so nasty here
    do {
        bool flag = true;
        for (unsigned int i = 0; i < selected_room->doors.size(); i++) {
            if (d1->hitbox.is_rect_overlap(selected_room->doors[i]->hitbox)) {
                flag = false;
                break;
            }
        }
        if (!flag) {
            d1->rand_pos();
        }else{
            break;
        }
    } while (true);
//    while (flag) {
//        flag = true;
//        for (unsigned int i = 0; i < selected_room->doors.size(); i++) {
//            if (d1->hitbox.is_rect_overlap(selected_room->doors[i]->hitbox)) {
//                flag = false;
//                break;
//            }
//        }
//        if (!flag) {
//            d1->rand_pos();
//        }
//    }
    //create the matching door
    Door * d2 = new Door(d1->get_opp_dir());
    Room * new_room = new Room();
    
    new_room->doors.push_back(d1); d1->next_room = selected_room;
    selected_room->doors.push_back(d2); d2->next_room = new_room;
    
    rooms.push_back(new_room);
}

void MainScreen::turn_end(){
    Instance::get().screen_shown = Instance::INTER_SCREEN;
    //Dialogue pool?
    std::stringstream ss; ss<<"Day ?"<<std::endl;
    //There should be normal text
    //But there should also be text driven by event
    Instance::get().inter_screen->text->set_text("Day ?");
    
    if(player->get_new_condtion() == Player::CREATE_ROOM){
        
    }else if(player->get_new_condtion() == Player::DESTROY_ROOM){
#warning NOT TESTED
        unsigned int max_tag = 0;
        unsigned int index = 0;
        for (unsigned int i = 0; i < rooms.size(); i++){
            if (rooms[i]->tag > max_tag) index = i;
        }
        Room * bad_room = rooms[index]; rooms.erase(rooms.begin() + index);
        //just pick the 1st door
        Door * d1 = bad_room->doors[0];
        Room * next_room = d1->next_room;
        
        for (unsigned int i = 0; i < next_room->doors.size(); i++) {
            if (next_room->doors[i]->next_room == bad_room) {
                Door * d2 = next_room->doors[i];
                next_room->doors.erase(next_room->doors.begin() + i);
                delete d2;
                break;
            }
        }
        delete bad_room;
    }

    //put player back to the root room
    for (unsigned int i =0 ; i < rooms.size(); i++) {
        rooms[i]->reset();
    }
    //TODO: spawn x in to the room
    
    //Go back to our room room
    main_room = rooms[0];
    main_room->player = player;
    player->turn_left = ONE_TURN_COST;
    turn_left->set_text("TL: 24");
    
}

