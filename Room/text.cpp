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


Text::Text(Point pos, std::string s):s(s){
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

    hitbox = Rect(pos, col_max * TEXT_WIDTH, row_count * TEXT_HEIGHT);
}

Text::~Text(){
    
}

void Text::render(){
    glPushMatrix();
    
    glColor4f(1, 1, 1, 0.5);
    hitbox.render();
    
    GLuint texture_ID = Instance::get().texture().get_texture(Texture::FONT);
    
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //split based on \n
    unsigned int i = 0;
    unsigned int j = 0;
    Point top = hitbox.points[0];
    glBegin(GL_QUADS);
    for (unsigned int counter = 0; counter < s.length() ; counter++) {
        if (s[counter] == '\n') {
            i = 0;
            j++;
        }else{
            if (isalpha(s[counter])) {
                unsigned int c = toupper(s[counter]) - 'A';
                
                glTexCoord2f(TEXT_CLIP[2*c], TEXT_CLIP[2*c + 1]); glVertex2f( top.x + i * TEXT_WIDTH, top.y + j * TEXT_HEIGHT );
                glTexCoord2f(TEXT_CLIP[2*c] + t_TEXT_WIDTH, TEXT_CLIP[2*c + 1]); glVertex2f( top.x +(i+1) * TEXT_WIDTH, top.y + j * TEXT_HEIGHT );
                glTexCoord2f(TEXT_CLIP[2*c] + t_TEXT_WIDTH, TEXT_CLIP[2*c + 1] + t_TEXT_HEIGHT);glVertex2f( top.x +(i+1) * TEXT_WIDTH, top.y + (j+1) * TEXT_HEIGHT );
                glTexCoord2f(TEXT_CLIP[2*c], TEXT_CLIP[2*c + 1] + t_TEXT_HEIGHT);glVertex2f( top.x +i * TEXT_WIDTH, top.y + (j+1) * TEXT_HEIGHT );
            }
            i++;
        }
    }
    
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    
}