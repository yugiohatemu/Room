//
//  interScreen.h
//  Room
//
//  Created by Yue Huang on 2014-04-14.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__interScreen__
#define __Room__interScreen__
#include <SDL2/SDL_events.h>
class Text;

class InterScreen{
    
public:
    Text * text;
    
    InterScreen();
    ~InterScreen();
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Room__interScreen__) */
