//
//  screen.h
//  Room
//
//  Created by Yue Huang on 2014-04-14.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef Room_screen_h
#define Room_screen_h

#include <SDL2/SDL_events.h>

class Screen{
public:
    Screen * root;
    Screen(){};
    virtual ~Screen(){root = NULL;};
    virtual void render() = 0;
    virtual void update(SDL_Event event) = 0;

};

#endif
