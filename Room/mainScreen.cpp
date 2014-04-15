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

MainScreen::MainScreen(){
    player = new Player();
    player->hitbox = Rect(Point(),40,120);
    //Central memory control of room and door
    Room * root_room = new Room();
    Room * test_room = new Room();
    
    Door * d1 = new Door();
    d1->hitbox = Rect(Point(320,50,0),30,40);
    root_room->doors.push_back(d1);
    
    Door * d2 = new Door();
    d2->hitbox = Rect(Point(320,400,0),30,40);
    test_room->doors.push_back(d2);
    
    d1->next_room = test_room;
    d2->next_room = root_room;
    
    rooms.push_back(root_room);
    rooms.push_back(test_room);
    
    set_main_room(root_room);
}

MainScreen::~MainScreen(){
    for (unsigned int i = 0; i < rooms.size(); i++) {
        if (rooms[i]) delete rooms[i];
    }
    delete player;
}

void MainScreen::set_main_room(Room * room){
    main_room = room;
    main_room->player = player;
//    main_room->reset(); why?
    //set the position of player
}

void MainScreen::render(){
    main_room->render();
}

void MainScreen::update(SDL_Event event){
    main_room->update(event);
}