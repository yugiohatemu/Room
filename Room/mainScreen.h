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
#include <vector>
class Room;
class Player;


class MainScreen{
public:
    Room * main_room;
    Player * player;
    std::vector<Room *> rooms;

    MainScreen();
    ~MainScreen();
    void render();
    void update(SDL_Event event);
    void set_main_room(Room * room);
};

#endif /* defined(__Room__mainScreen__) */
