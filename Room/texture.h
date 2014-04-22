//
//  texture.h
//  Room
//
//  Created by Yue Huang on 2014-04-10.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__texture__
#define __Room__texture__

#include <SDL2/SDL_opengl.h>
#include <string>
#include <vector>

class Texture{
    
public:
    enum{
        ITEM,
        TOTAL_TEXTURE,
    }TEXTURE_TYPE;
    
    std::vector<GLuint> textureList;
    int load_file(const char * fileName,unsigned int width,unsigned int height);
    void clean_texture();
    GLuint get_texture(GLuint type);
};
#endif /* defined(__Room__texture__) */
