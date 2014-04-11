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

Text::Text(std::string s){
    
}

Text::~Text(){
    
}

void Text::render(){
    glPushMatrix();
    
    //get texture
    GLuint texture_ID = Instance::get().texture().get_texture(Texture::FONT);

    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //split based on \n
    unsigned int i = 0;
    unsigned int j = 0;
    glBegin(GL_QUADS);
    for (unsigned int counter = 0; counter < s.length() ; counter++) {
        if (s[counter] == '\n') {
            i = 0;
            j++;
        }else{
            if (s[counter] != ' ') {
                glVertex2f( i * 32, j * 32 ); glTexCoord2f( 0 ,0 );
                glVertex2f( i * 32 + 32, j * 32 ); glTexCoord2f( 0 ,0 );
                glVertex2f( i * 32 + 32, j * 32 + 32 ); glTexCoord2f( 0 ,0 );
                glVertex2f( i * 32, j * 32 + 32); glTexCoord2f( 0 ,0 );
            }
            i++;
        }
    }
    
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    
}