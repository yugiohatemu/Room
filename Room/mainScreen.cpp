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
    show_health = false;
    //Central memory control of room and door
    Room * root_room = new Room();
    rooms.push_back(root_room);
    main_room = root_room;
    main_room->player = player;
    health_screen = new Text(Point(320, 200,0), "HP:  \nMP:  \nX:  ");
    
    //Create main room here
    Item *bed = new Item();
    bed->hitbox = Rect(Point(50,50,0),150,200);
    bed->type = ITEM_BED;
    bed->turn_cost = 7;
    bed->mh_charge = 10;
    bed->ph_charge = 15;
    bed->options[0] = new Text(Point(125, 150,0),"INFO");
    bed->options[1] = new Text(Point(125, 150 + TEXT_HEIGHT,0),"USE");
    bed->info = new Text(Point(0, 400,0),"This is a comfortable bed");
//    bed->event = "I slept.\n"; //good? bad? average? Had dreams?
    //yap...
    Item *X = new Item();
    X->hitbox = Rect(Point(500, 50, 0),80 ,80);
    X->type = ITEM_X;
    X->turn_cost = 5;
    X->mh_charge = -10;
    X->ph_charge = -10;
    X->options[0] = new Text(Point(540, 90,0),"INFO");
    X->options[1] = new Text(Point(540, 90 + TEXT_HEIGHT,0),"USE");
    X->info = new Text(Point(0, 400,0),"This is X");
//    X->event = "I did X\n";//If goes well? not well? bad? stuck?
    //
    Item *book = new Item();
    book->hitbox = Rect(Point(50, 350, 0),100 ,60);
    book->type = ITEM_BOOK;
    book->turn_cost = 5;
    book->mh_charge = 5;
    book->ph_charge = -10;
    book->options[0] = new Text(Point(100, 380,0),"INFO");
    book->options[1] = new Text(Point(100, 380 + TEXT_HEIGHT,0),"USE");
    book->info = new Text(Point(0, 400,0),"There are many books in it");
//    book->event = "I read books\n"; //it inspired me? depress me? or what?
    //Or may be we could just record item_type? and form string latter?
    
    root_room->all_items.push_back(bed);
    root_room->all_items.push_back(X);
    root_room->all_items.push_back(book);
   
}

MainScreen::~MainScreen(){
    for (unsigned int i = 0; i < rooms.size(); i++) {
        if (rooms[i]) delete rooms[i];
    }
    delete player;
}

void MainScreen::render(){
    main_room->render();
    if (show_health) {
        //health_screen->set_text_with_player_stat();
        health_screen->render();
    }
}

void MainScreen::update(SDL_Event event){
    if (event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_ESCAPE) show_health = !show_health ;
    }
    main_room->update(event);
}

void MainScreen::turn_end(){
    Instance::get().screen_shown = Instance::INTER_SCREEN;
    //Dialogue pool?
    std::stringstream ss; ss<<"Day ?"<<std::endl;
    //There should be normal text
    //But there should also be text driven by event
    Instance::get().inter_screen->text->set_text("Day ?");
    
    if(player->get_new_condtion() == Player::CREATE_ROOM){
       
        Room * new_room = new Room();
        //In the latter, we can pull a random item outside of our item pool and charge it
        Item *book = new Item();
        book->hitbox = Rect(Point(50, 350, 0),100 ,60);
        book->type = ITEM_BOOK;
        book->turn_cost = 5;
        book->mh_charge = 5;
        book->ph_charge = -10;
        book->options[0] = new Text(Point(100, 380,0),"INFO");
        book->options[1] = new Text(Point(100, 380 + TEXT_HEIGHT,0),"USE");
        book->info = new Text(Point(0, 400,0),"There are many books in it");
        new_room->all_items.push_back(book);
        
        Room * prev_room = rooms[rooms.size()-1];
        
        Door * d1 = new Door(Door::get_rand_dir()); //pick a direction, and find the matching direction with it
        Door * d2 = new Door(d1->get_opp_dir());
        
        new_room->doors.push_back(d1); d1->next_room = prev_room;
        prev_room->doors.push_back(d2); d2->next_room = new_room;
        
        rooms.push_back(new_room);
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
    
    //Go back to our room room
    main_room = rooms[0];
    main_room->player = player;
    player->turn_left = ONE_TURN_COST;
    show_health = false;
}

