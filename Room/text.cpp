//
//  text.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-10.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "text.h"
#include "instance.h"
#include <OpenGL/OpenGL.h>
#include <SDL2/SDL_opengl.h>
#include <ctype.h>
#include <GLUT/GLUT.h>

Text::Text(Point pos, std::string t){
    hitbox.top_left = pos;
    set_text(t);
}

void Text::set_text(std::string t){
    s = t;
    
    unsigned row_count = 1;
    unsigned col_count = 0;
    unsigned col_max = 0;
    
    for (unsigned int i = 0 ; i < s.length(); i++) {
        if (s[i] == '\n') {
            col_max = std::max(col_max, col_count);
            col_count = 0;
            row_count++;
        }else{
            col_count++;
        }
    }
    col_max = std::max(col_max, col_count);
    if (col_max * TEXT_WIDTH > SCREEN_WIDTH) {
        text_width = SCREEN_WIDTH /(float) col_max;
    }else{
        text_width = TEXT_WIDTH;
    }
    text_height = TEXT_HEIGHT;
    
    hitbox.width = col_max * text_width;
    hitbox.height = row_count * text_height;

}


Text::~Text(){
    
}

void Text::render(){
    glPushMatrix();
    glColor4f(1, 1, 1, 0.5);
    hitbox.render();
    glColor3f(0, 0, 0);
    //split based on \n
    unsigned int j = 0;

    glRasterPos2f(hitbox.top_left.x, hitbox.top_left.y + 24);
    for (unsigned int i = 0; i < s.length() ; i++) {
        if (s[i] == '\n') {
            j++;
            glRasterPos2f(hitbox.top_left.x, hitbox.top_left.y + 24 + 30 * j);
        }else{
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
        }
    }
    
    glPopMatrix();
    
}