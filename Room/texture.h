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
private:
    Texture();  // Private so that it can  not be called
    Texture(Texture const&);             // copy constructor is private
    Texture& operator=(Texture const&);  // assignment operator is private
    
    unsigned int height;
    unsigned int width;
    
public:
    enum{
        MARBLE,
        TILE,
        FONT,
        TOTAL_TEXTURE,
    }TEXTURE_TYPE;
    
    std::vector<GLuint> textureList;
    
    static Texture& Instance();
    int load_file(const char * fileName,unsigned int width,unsigned int height);
    void clean_texture();
    //    void use_texture();
    GLuint get_texture(GLuint type);
    //static void unbind_texture();
};
#endif /* defined(__Room__texture__) */
