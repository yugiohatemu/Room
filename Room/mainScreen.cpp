//
//  mainScreen.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-14.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "mainScreen.h"
#include "mainRoom.h"

MainScreen::MainScreen(){
    main_room = new MainRoom();
}
MainScreen::~MainScreen(){
    delete main_room;
}

void MainScreen::render(){
    main_room->render();
}

void MainScreen::update(SDL_Event event){
    main_room->update(event);
}