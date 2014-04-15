//
//  instance.h
//  Room
//
//  Created by Yue Huang on 2014-04-10.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__instance__
#define __Room__instance__

#include "texture.h"
#include "const.h"
#include <SDL2/SDL_events.h>

class InterScreen;
class MainScreen;

class Instance{
private:
    Instance();  // Private so that it can  not be called
    Instance(Instance const&);             // copy constructor is private
    Instance& operator=(Instance const&);  // assignment operator is private
    Texture m_texture;
public:
    enum SCREEN_SHOWN{
        MENU_SCREEN,
        INTER_SCREEN,
        MAIN_SCREEN,
    };
    SCREEN_SHOWN screen_shown;
    
    InterScreen * inter_screen;
    MainScreen * main_screen;
    
    static Instance& get();
    void load_all();
    void clean_all();
    Texture& texture();
    void render();
    void update(SDL_Event event);
};


#endif /* defined(__Room__instance__) */
