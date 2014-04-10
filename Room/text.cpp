//
//  text.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-10.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "text.h"
#include "texture.h"
#include <OpenGL/OpenGL.h>
#include <SDL2/SDL_opengl.h>

Text::Text(std::string s){
    
}

Text::~Text(){
    
}

void Text::render(){
    glPushMatrix();
    
    //get texture
    GLuint texture_ID = Texture::Instance().get_texture(Texture::FONT);
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //start drawing
    glLoadIdentity();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    
}