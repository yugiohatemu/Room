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
#include "clip.h"
#include <ctype.h>

Text::Text(Rect rect, std::string s):s(s), rect(rect){
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
//
    col_size = rect.width() /(float) col_max;
    row_size = rect.height() / (float) row_count;
}

Text::~Text(){
    
}

void Text::render(){
    glPushMatrix();
    glColor3f(1, 1, 1);
    rect.render();
    
    //get texture
    GLuint texture_ID = Instance::get().texture().get_texture(Texture::FONT);
    
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //split based on \n
    unsigned int i = 0;
    unsigned int j = 0;
    Point top = rect.points[0];
    glBegin(GL_QUADS);
    for (unsigned int counter = 0; counter < s.length() ; counter++) {
        if (s[counter] == '\n') {
            i = 0;
            j++;
        }else{
            if (isalpha(s[counter])) {
                unsigned int c = toupper(s[counter]) - 'A';
                
                glTexCoord2f( TEXT_CLIP[2*c], TEXT_CLIP[2*c + 1]); glVertex2f( top.x + i * col_size, top.y + j * row_size );
                glTexCoord2f(TEXT_CLIP[2*c] + TEXT_WIDTH, TEXT_CLIP[2*c + 1]); glVertex2f( top.x +(i+1) * col_size, top.y + j * row_size );
                glTexCoord2f(TEXT_CLIP[2*c] + TEXT_WIDTH, TEXT_CLIP[2*c + 1] + TEXT_HEIGHT);glVertex2f( top.x +(i+1) * col_size, top.y + (j+1) * row_size );
                glTexCoord2f(TEXT_CLIP[2*c], TEXT_CLIP[2*c + 1] + TEXT_HEIGHT);glVertex2f( top.x +i * col_size, top.y + (j+1) * row_size );
            }
            i++;
        }
    }
    
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    
}