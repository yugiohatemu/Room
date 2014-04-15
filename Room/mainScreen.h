//
//  mainScreen.h
//  Room
//
//  Created by Yue Huang on 2014-04-14.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__mainScreen__
#define __Room__mainScreen__

#include <SDL2/SDL_events.h>

class MainRoom;

class MainScreen{
public:
    MainRoom * main_room;
    MainScreen();
    ~MainScreen();
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Room__mainScreen__) */
